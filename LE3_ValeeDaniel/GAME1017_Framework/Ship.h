#ifndef __SHIP_H__
#define __SHIP_H__
#include "GameObject.h"
#include "BulletPool.h"
#include <vector>

class Ship : public AnimatedSprite
{
public: // Methods.
	Ship(SDL_Rect s, SDL_FRect d);
	~Ship();
	void Update();
	void Render();
	const double& GetRadius();
	void TeleportShip(); // New requirement for LE3.
private: // Properties.
	SDL_FPoint m_center;
	double m_angle,
		m_dx, m_dy,
		m_velX, m_velY,
		m_velMax,
		m_radius,
		m_rotSpeed,
		m_thrust;
};

#endif