#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__
#include <SDL_rect.h>

class GameObject
{
public:
	GameObject(const SDL_FRect);
	SDL_FRect* GetDst();
	SDL_FPoint GetCenter() const;

protected: // private but inherited.
	SDL_FRect m_dst;
};

class Sprite : public GameObject
{
public:
	Sprite(const SDL_Rect src, const SDL_FRect dst);
	SDL_Rect* GetSrc();
protected:
	SDL_Rect m_src;
};

#endif

