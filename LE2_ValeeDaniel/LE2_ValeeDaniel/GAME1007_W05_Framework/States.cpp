#include <iostream>
#include "States.h"
#include "StateManager.h"
#include "CollisionManager.h"
#include "EventManager.h"
#include "RenderManager.h"
#include "TextureManager.h"

using namespace std;
using namespace tinyxml2;

void State::Render()
{
	SDL_RenderPresent(REMA::Instance().GetRenderer());
}

TitleState::TitleState(){}

void TitleState::Enter()
{
	
}

void TitleState::Update()
{
	if (EVMA::KeyPressed(SDL_SCANCODE_N))
	{
		STMA::ChangeState( new GameState() );
	}
}

void TitleState::Render()
{
	SDL_SetRenderDrawColor(REMA::Instance().GetRenderer(), 0, 0, 255, 255);
	SDL_RenderClear(REMA::Instance().GetRenderer());
	State::Render();
}

void TitleState::Exit()
{
	
}

void GameState::ClearTurrets()
{
	for (unsigned i = 0; i < m_turrets.size(); i++)
	{
		delete m_turrets[i];
		m_turrets[i] = nullptr;
	}
	m_turrets.clear();
	m_turrets.shrink_to_fit();
	// You can assimilate some parts of this code for deleting bullets and enemies.
}
GameState::GameState():m_spawnCtr(1) {}

void GameState::Enter()
{
	TEMA::Load("../Assets/img/Turret.png", "Turret");
	TEMA::Load("../Assets/img/Enemies.png", "enemy");
	s_enemies.push_back(new Enemy({ 80,0,40,57 }, { 512.0f, -57.0f, 40.0f, 57.0f }));
	// Create the DOM and load the XML file.
	// Iterate through the Turret elements in the file and push_back new Turrets into the m_turrets vector.
		// Keep the width and height as 100.
	// Look at the last two XML examples from Week 3
	xmldoc.LoadFile("../Assets/dat/Turrets.xml");
	XMLElement* pRoot = xmldoc.FirstChildElement();
	if (pRoot == nullptr)
	{
		return;
	}
	XMLElement* pElement = pRoot->FirstChildElement();
	while (pElement != nullptr)
	{
		if (strcmp(pElement->Value(), "Turret") == 0)
		{
			float x = pElement->FloatAttribute("x.Position");
			float y = pElement->FloatAttribute("y.Position");
			int kills = pElement->IntAttribute("kills");
			auto turret = new Turret({ 0,0,100,100 }, { x,y,100.f,100.f });
			m_turrets.push_back(turret);

		}
		pElement = pElement->NextSiblingElement();
	}
}
void GameState::Update()
{
	// Parse T and C events.
	if (EVMA::KeyPressed(SDL_SCANCODE_T))
	{
		m_turrets.push_back(new Turret({0,0,100,100},
			{50.0f, 615.0f, 100.0f,100.0f}));
	}
	if (EVMA::KeyPressed(SDL_SCANCODE_C))
	{
		ClearTurrets();
	}
	// Update all GameObjects individually. Spawn enemies. Update turrets. Update enemies. Update bullets.
	if (m_spawnCtr++ % 180 == 0)
	{
		s_enemies.push_back(new Enemy({ 80,0,40,57 },
			{ (float)(rand() % (1024 - 40)), -57.0f, 40.0f, 57.0f }));
	}
	for (auto turret : m_turrets)
		turret->Update();
	for (auto enemy : s_enemies)
		enemy->Update();
	for (auto bullet : s_bullets)
		bullet->Update();
	for (auto bullet : s_bullets)
	{
	  for (auto enemy : s_enemies)
	  {
		 if (COMA::AABBCheck(*bullet->GetDst(), *enemy->GetDst()))
		 {
			bullet->m_Parents->m_Killcounter + 1;
			 enemy->m_deleteMe = true;
			  bullet->m_deleteMe = true;
			break;
	     }
	  }
	}
	 for (int i = 0; i < static_cast<int>(s_bullets.size()); ++i)
	 {
	 	if (s_bullets[i]->m_deleteMe == true)
		{
		  delete s_bullets[i];
			s_bullets[i] = nullptr;
			 s_bullets.erase(s_bullets.begin() + i);
		    s_bullets.shrink_to_fit();
		}
	 }
	for (int i = 0; i < static_cast<int>(s_enemies.size()); ++i)
	{
		if (s_enemies[i]->m_deleteMe == true)
		{
		  delete s_enemies[i];
			s_enemies[i] = nullptr;
			 s_enemies.erase(s_enemies.begin() + i);
			s_enemies.shrink_to_fit();
		}
	}
}
void GameState::Render()
{
	SDL_SetRenderDrawColor(REMA::Instance().GetRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(REMA::Instance().GetRenderer());

	for (unsigned i = 0; i < m_turrets.size(); i++)
		m_turrets[i]->Render();
	for (unsigned i = 0; i < s_enemies.size(); i++)
		s_enemies[i]->Render();
	for (unsigned i = 0; i < s_bullets.size(); i++)
		s_bullets[i]->Render();
	// This code below prevents SDL_RenderPresent from running twice in one frame.
	if ( dynamic_cast<GameState*>( STMA::GetStates().back() ) ) // If current state is GameState.
		State::Render();
}

void GameState::Exit()
{
	// You can clear all children of the root node by calling .DeleteChildren(); and this will essentially clear the DOM.

	// Iterate through all the turrets and save their positions as child elements of the root node in the DOM.
	xmldoc.DeleteChildren();
	XMLNode* pRoot = xmldoc.NewElement("Info");
	xmldoc.InsertEndChild(pRoot);
	XMLElement* pElement;
	for (auto turret : m_turrets)
	{
		pElement = xmldoc.NewElement("Turret");
		pElement->SetAttribute("x.Position", turret->GetDst()->x);
		pElement->SetAttribute("y.Position", turret->GetDst()->y);
		pElement->SetAttribute("kills", turret->m_Killcounter);
		pRoot->InsertEndChild(pElement);
	}
	// Make sure to save to the XML file.
	 xmldoc.SaveFile("../Assets/dat/Turrets.xml");
	ClearTurrets(); // Deallocate all turrets, then all other objects.
	for (unsigned i = 0; i < s_enemies.size(); i++)
	{
		delete s_enemies[i];
		s_enemies[i] = nullptr;
	}
	s_enemies.clear();
	s_enemies.shrink_to_fit();
	for (unsigned i = 0; i < s_bullets.size(); i++)
	{
		delete s_bullets[i];
		s_bullets[i] = nullptr;
	}
	s_bullets.clear();
	s_bullets.shrink_to_fit();
}

void GameState::Resume()
{
	
}
// This is how static properties are allocated.
std::vector<Bullet*> GameState::s_bullets;
std::vector<Enemy*> GameState::s_enemies;