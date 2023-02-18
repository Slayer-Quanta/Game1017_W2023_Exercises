#ifndef __TURRET_H__
#define __TURRET_H__
#include <SDL.h>
#include "GameObject.h"

class Turret : public Sprite
{
public:
	Turret(const SDL_Rect, const SDL_FRect);
	void Update();
	void Render();

	int m_Killcounter = 0;

private:
	double m_angle;
	// Firing properties.
	bool m_hasTarget;
	int m_fireCtr;
	static int s_coolDown;
};

#endif