#ifndef __BULLETPOOL_H__
#define __BULLETPOOL_H__
#include <SDL.h>
#include <string>
#include <vector>
#include "GameObject.h"

class Bullet : public Sprite
{
public:
	Bullet(SDL_Rect, SDL_FRect, const char*, const double);
	void Update();
	void Render();
	const SDL_FPoint& GetCenter();
	const double& GetRadius();
	double GetAngle();
private:
	SDL_FPoint m_center;
	int m_ctr, m_ctrMax;
	double m_angle,
		m_dx, m_dy,
		m_radius;
	std::string m_key;
};

class BulletPool : public GameObject
{
public:
	~BulletPool();
	void Update();
	void Render();
	void Fire(SDL_FPoint, double);
	std::vector<Bullet*>& GetBullets();
private:
	std::vector<Bullet*> m_bullets;
};

#endif