#ifndef __MATHMANAGER_H__
#define __MATHMANAGER_H__
#include <algorithm>
#include <cmath>
#include "SDL.h"

class MathManager
{
public: // Public methods.
	static double Distance(const double&, const double&, const double&, const double&);
	static double Distance(const SDL_FRect*, const SDL_FRect*);
	static double Distance(const SDL_FPoint*, const SDL_FPoint*);
	static SDL_FPoint Normalize(SDL_FPoint);
	static double AngleBetweenPoints(const double, const double);
	static void SetDeltas(const double, double&, double&, double = 1.0, double = 1.0);
	static double SetDeltaX(const double, double = 1.0);
	static double SetDeltaY(const double, double = 1.0);
	static double Deg2Rad(const double);
	static double Rad2Deg(const double);
	static SDL_Rect ConvertFRect2Rect(const SDL_FRect&);
	static SDL_Point ConvertFPoint2Point(const SDL_FPoint&);
	static double Angle180(double);
	static double Angle360(double);
	static double LerpD(double, double, double);
	static double LerpRad(double, double, double);
	static SDL_Point HalfwayPoint(const SDL_Point&, const SDL_Point&);
	static int ClampI(const int, const int, const int);

private: // Private properties.
	MathManager() = default;
};

typedef MathManager MAMA;

#endif