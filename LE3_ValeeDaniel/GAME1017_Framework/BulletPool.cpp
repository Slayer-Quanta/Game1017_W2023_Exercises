#include "BulletPool.h"
#include "Engine.h"
#include "MathManager.h"
#include "RenderManager.h"
#include "TextureManager.h"

Bullet::Bullet(SDL_Rect s, SDL_FRect d, const char* key, const double angle) :
	Sprite(s, d), m_key(key), m_angle(angle), m_radius(10),
	m_ctr(0), m_ctrMax(75)
{
	m_center = { (m_dst.x + m_dst.w / 2.0f), (m_dst.y + m_dst.h / 2.0f) };
	MAMA::SetDeltas(MAMA::Deg2Rad(m_angle - 90.0), m_dx, m_dy, 10.0f, 10.0f);
}

void Bullet::Update()
{
	// Move object.
	m_center.x += (float)m_dx;
	m_center.y += (float)m_dy;
	// Wrap on screen.
	if (m_center.x < -m_dst.w) m_center.x = kWidth + m_dst.w / 2;
	else if (m_center.x > kWidth + m_dst.w) m_center.x = 0 - m_dst.w / 2;
	else if (m_center.y < -m_dst.h) m_center.y = kHeight + m_dst.h / 2;
	else if (m_center.y > kHeight + m_dst.h) m_center.y = 0 - m_dst.h / 2;
	// Update dest rectangle.
	m_dst.x = m_center.x - m_dst.w / 2;
	m_dst.y = m_center.y - m_dst.h / 2;
	// Set bullet to be disabled.
	if (m_ctr++ >= m_ctrMax)
		m_enabled = false;
}

void Bullet::Render()
{
	SDL_RenderCopyExF(REMA::GetRenderer(), TEMA::GetTexture(m_key),
		&m_src, &m_dst, m_angle, nullptr, SDL_FLIP_NONE);
}

const SDL_FPoint& Bullet::GetCenter()
{
    return m_center;
}

const double& Bullet::GetRadius()
{ 
    return m_radius; 
}

double Bullet::GetAngle()
{
	return m_angle;
}

BulletPool::~BulletPool()
{
	for (auto bullet : m_bullets)
	{
		delete bullet;
		bullet = nullptr;
		m_bullets.clear();
		m_bullets.shrink_to_fit();
	}
}

void BulletPool::Update()
{
	for (unsigned int i = 0; i < m_bullets.size(); i++)
	{
		if (m_bullets[i]->GetEnabled() == false)
		{
			delete m_bullets[i];
			m_bullets[i] = nullptr;
			m_bullets.erase(m_bullets.begin() + i);
			m_bullets.shrink_to_fit();
			return;
		}
		m_bullets[i]->Update();
	}
}

void BulletPool::Render()
{
	for (const auto bullet : m_bullets)
		bullet->Render();
}

void BulletPool::Fire(SDL_FPoint center, double angle)
{
	m_bullets.push_back(new Bullet({ 500, 0, 18, 24 },
		{ center.x - 9, center.y - 12, 18, 24 },
		"sprites", angle));
	m_bullets.shrink_to_fit();
}

std::vector<Bullet*>& BulletPool::GetBullets()
{
	return m_bullets;
}
