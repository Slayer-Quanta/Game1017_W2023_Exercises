#include "Bullet.h"
#include "Engine.h"
#include "RenderManager.h"
#include <iostream>
Bullet::Bullet(const SDL_FRect dst, const double dx, const double dy):GameObject(dst), m_dx(dx), m_dy(dy) { }

void Bullet::Update()
{
	m_dst.x += (float)m_dx * s_speed * (float)Engine::Instance().GetDeltaTime();
	m_dst.y += (float)m_dy * s_speed * (float)Engine::Instance().GetDeltaTime();
	// Optional method of cleaning bullets.
	// if bullet goes off screen (four bounds checks)
		// flip deleteMe flag to true.
}

void Bullet::Render()
{
	SDL_SetRenderDrawColor(REMA::Instance().GetRenderer(), 240, 255, 0, 255);
	SDL_RenderFillRectF(REMA::Instance().GetRenderer(), &m_dst);
}

const float Bullet::s_speed = 300.0f;
