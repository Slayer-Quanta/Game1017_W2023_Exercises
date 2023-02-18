#include "Turret.h"
#include "States.h"
#include "Enemy.h"
#include "Bullet.h"
#include "CollisionManager.h"
#include "EventManager.h"
#include "MathManager.h"
#include "RenderManager.h"
#include "TextureManager.h"

Turret::Turret(const SDL_Rect src, const SDL_FRect dst) :Sprite(src, dst), m_angle(0.0), m_hasTarget(false), m_fireCtr(0)
{
	
}

void Turret::Update()
{
	if (m_fireCtr > 0) m_fireCtr--; // Always reload turret.
	// Click and drag functionality. Note there is SDL_PointInFRect but the Point is float too.
	if (EVMA::MouseHeld(1) && COMA::PointAABBCheck(EVMA::GetMousePos(), m_dst))
	{
		m_dst.x = EVMA::GetMousePos().x - m_dst.w / 2.0f;
		m_dst.y = EVMA::GetMousePos().y - m_dst.h / 2.0f;
	}
	m_angle = 0.0;
	m_hasTarget = false;
	// If there are no Enemies, turret shouldn't acquire target. So, return.
	if (GameState::Enemies().size() == 0) return;
	// Store center points of closest enemy and turret. For distance check.
	SDL_FPoint turretCenter = this->GetCenter();
	SDL_FPoint closestEnemy = GameState::Enemies()[0]->GetCenter();
	// Find closest enemy.
	for (unsigned i = 1; i < GameState::Enemies().size(); i++)
	{
		SDL_FPoint nextEnemy = GameState::Enemies()[i]->GetCenter();
		if (MAMA::Distance(&turretCenter, &nextEnemy) <
			MAMA::Distance(&turretCenter, &closestEnemy))
		{
			closestEnemy = nextEnemy;
		}
	}
	// Is the closest enemy <= 300px away?
	if (MAMA::Distance(&turretCenter, &closestEnemy) <= 300.0)
	{
		// Track closest enemy.
		SDL_FPoint deltaVector = { closestEnemy.x - turretCenter.x, closestEnemy.y - turretCenter.y + 30.0f };
		m_angle = MAMA::Rad2Deg(MAMA::AngleBetweenPoints(deltaVector.y, deltaVector.x)) + 90.0;
		m_hasTarget = true;
		if (m_fireCtr == 0) // Is turret ready to fire?
		{
			SDL_FPoint normalVector = MAMA::Normalize(deltaVector);
			GameState::Bullets().push_back(new Bullet({ turretCenter.x - 2.0f, turretCenter.y - 2.0f , 4.0f, 4.0f },
				normalVector.x, normalVector.y));
			m_fireCtr = s_coolDown;
		}
	}
	if (m_fireCtr > 0) m_fireCtr--; // Always reload turret.
}

void Turret::Render()
{
	SDL_RenderCopyExF(REMA::Instance().GetRenderer(), TEMA::GetTexture("Turret"),
		&m_src, &m_dst, m_angle, NULL, SDL_FLIP_NONE);
}

int Turret::s_coolDown = 120;