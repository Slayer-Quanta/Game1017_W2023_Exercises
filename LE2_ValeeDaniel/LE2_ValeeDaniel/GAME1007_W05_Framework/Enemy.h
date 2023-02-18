#ifndef __ENEMY_H__
#define __ENEMY_H__
#include <SDL.h>
#include "GameObject.h"

class Enemy : public Sprite
{
public:
	Enemy(const SDL_Rect, const SDL_FRect);
	void Update();
	void Render();
	bool m_deleteMe = false;
private:
	static const float s_speed; // Common to all enemies. Also just showing a static property again.
};

#endif