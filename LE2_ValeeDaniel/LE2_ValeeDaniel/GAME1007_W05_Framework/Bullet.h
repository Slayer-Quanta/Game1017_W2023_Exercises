#ifndef __BULLET_H__
#define __BULLET_H__
#include <SDL.h>
#include "GameObject.h"
#include "Turret.h"
class Bullet : public GameObject
{
private:
	double m_dx, m_dy;
	static const float s_speed;

public:
	Bullet(const SDL_FRect, const double, const double);
	void Update();
	void Render();
	 bool m_deleteMe = false;
	 Turret* m_Parents;
	// bool deleteMe; // Flag that will let the program know, we can delete it.
};

#endif