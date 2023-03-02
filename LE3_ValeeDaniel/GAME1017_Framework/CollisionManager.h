#ifndef __COLLISIONMANAGER_H__
#define __COLLISIONMANAGER_H__
#include <iostream>
#include <SDL.h>
#include "MathManager.h"

class CollisionManager
{
public:
	// AABB-AABB overloads.
	static bool AABBCheck(const SDL_Rect&, const SDL_Rect&); // Two int-based Rects.
	static bool AABBCheck(const SDL_Rect&, const SDL_FRect&); // Int-based Rect, Float-based Rect.
	static bool AABBCheck(const SDL_FRect&, const SDL_FRect&); // Two float-based Rects.

	// AABB-Line overloads.
	static bool AABBLineCheck(const SDL_Rect&, SDL_Point, SDL_Point); // Int-based.
	static bool AABBLineCheck(const SDL_FRect&, SDL_Point, SDL_Point); // Int-based line, Float-based Rect.
	static bool AABBLineCheck(const SDL_FRect&, SDL_FPoint, SDL_FPoint); // Float-based.

	// Circle-AABB overloads.
	static bool CircleAABBCheck(const SDL_Point, const double, const SDL_Rect&); // Int-based.
	static bool CircleAABBCheck(const SDL_FPoint, const double, const SDL_FRect&); // Float-based.

	// Circle-Circle overloads.
	static bool CircleCircleCheck(const SDL_Point, const SDL_Point, const double, const double = 0.0); // Int-based.
	static bool CircleCircleCheck(const SDL_FPoint, const SDL_FPoint, const double, const double = 0.0); // Float-based.
	
	// Line-Point overloads.
	static bool LinePointCheck(const SDL_Point, const SDL_Point object1_end, const SDL_Point object2); // Int-based.
	static bool LinePointCheck(const SDL_FPoint, const SDL_FPoint object1_end, const SDL_FPoint object2); // Float-based.

	// Point-AABB overloads.
	static bool PointAABBCheck(const SDL_Point, const SDL_Rect&); // Int-based.
	static bool PointAABBCheck(const SDL_Point, const SDL_FRect&); // Int-based point, Float-based Rect.
	static bool PointAABBCheck(const SDL_FPoint, const SDL_FRect&); // Float-based.
private:
	CollisionManager() = default;
};

typedef CollisionManager COMA;

#endif