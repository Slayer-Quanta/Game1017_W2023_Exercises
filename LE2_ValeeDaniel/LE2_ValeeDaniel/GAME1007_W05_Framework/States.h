#ifndef __STATES_H__
#define __STATES_H__
#include "Turret.h"
#include "Bullet.h"
#include "Enemy.h"
#include <vector>
#include "tinyxml2.h"

// An abstract class is one that cannot be instantiated. 
// Why? Because they'd be a base class most likely.
class State // This is the abstract base class for all state subclasses.
{
public:
	virtual void Enter() = 0; // = 0 means pure virtual. Method MUST be defined in subclass.
	virtual void Update() = 0;
	virtual void Render();
	virtual void Exit() = 0;
	virtual void Resume() {};
protected: // Private but inherited.
	State() = default;
};

class TitleState : public State
{
public:
	TitleState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
private:

};

class GameState : public State
{
public:
	GameState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
	virtual void Resume();
	static std::vector<Bullet*>& Bullets() { return s_bullets; }
	static std::vector<Enemy*>& Enemies() { return s_enemies; }
private:

	tinyxml2::XMLDocument xmldoc;
	std::vector<Turret*> m_turrets;
	static std::vector<Enemy*> s_enemies; // Didn't need to be static. Spawning enemies from this class.
	static std::vector<Bullet*> s_bullets; // Static because Turret class is spawning bullets.
	int m_spawnCtr; // Enemy spawn counter.
	void ClearTurrets();
};
#endif