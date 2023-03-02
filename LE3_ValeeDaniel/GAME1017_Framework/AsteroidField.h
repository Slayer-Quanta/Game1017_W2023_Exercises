#ifndef __ASTEROIDFIELD_H__
#define __ASTEROIDFIELD_H__
#include "GameObject.h"
#include <SDL.h>
#include <vector>
#include <string>

class Asteroid : public Sprite
{
public:
	Asteroid(SDL_Rect s, SDL_FRect d);
	void Update();
	void Render();
	const SDL_FPoint& GetCenter() { return m_center; }
	const double& GetRadius() { return m_radius; }
	Uint8* GetColMods();
	void SetColMods(Uint8 r, Uint8 g, Uint8 b);
	short GetSize();
	void SetSize(short);
	void UpdateDeltas(double);
	
private:
	SDL_FPoint m_center;
	double m_angle,
		m_dx, m_dy,
		m_radius,
		m_rotSpeed;
	Uint8 m_rMod, m_gMod, m_bMod;
	short m_size; // New size field. 2 -> 1 -> gone.
};

class AsteroidField : public GameObject
{ // Manager class for the individual asteroids.
public:
	AsteroidField(unsigned int sz = 6);
	~AsteroidField();
	void Update();
	void Render();
	std::vector<Asteroid*>& GetAsteroids() { return m_asteroids; }
	const unsigned int GetSize() { return m_size; }
private:
	std::vector<Asteroid*> m_asteroids;
	int m_size;
};

#endif