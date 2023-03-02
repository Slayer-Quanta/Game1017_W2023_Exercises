#include <iostream>
#include "States.h"
#include "StateManager.h"
// GameObject includes.
#include "AsteroidField.h"
#include "BulletPool.h"
#include "Button3.h"
#include "Primitives.h"
#include "Ship.h"
// Remaining managers.
#include "CollisionManager.h"
#include "EventManager.h"
#include "RenderManager.h"
#include "SoundManager.h"
#include "TextureManager.h"

#include <iostream>
using namespace std;

void State::Update()
{
	for (auto const& i : m_objects)
	{
		i.second->Update();
		if (STMA::StateChanging()) return;
	}
}

void State::Render()
{
	for (auto const& i : m_objects)
		i.second->Render();
	if (dynamic_cast<GameState*>(this) && dynamic_cast<PauseState*>(STMA::GetStates().back())) 
		return; // If GameState is rendering but PauseState is the current state, return.
	SDL_RenderPresent(REMA::GetRenderer());
}

void State::Exit()
{
	for (auto& i : m_objects)
	{
		delete i.second;
		i.second = nullptr;
	}
	m_objects.clear();
	m_objects.shrink_to_fit();
}

void State::AddChild(std::string key, GameObject* obj)
{
	m_objects.push_back(pair<string, GameObject*>(key, obj));
}

GameObject* State::GetChild(const std::string& key)
{
	auto it = std::find_if(m_objects.begin(), m_objects.end(),
		[&](const std::pair<std::string, GameObject*>& element)
		{
			return element.first == key;
		});
	if (it != m_objects.end())
		return it->second;
	else return nullptr;
}

void State::RemoveChild(const std::string& key)
{
	auto it = std::find_if(m_objects.begin(), m_objects.end(),
		[&](const std::pair<std::string, GameObject*>& element)
		{
			return element.first == key;
		});
	if (it != m_objects.end())
	{
		delete it->second; // Deallocate GameObject.
		it->second = nullptr; // Wrangle dangle.
		m_objects.erase(it);
		m_objects.shrink_to_fit();
	}
}

// Begin TitleState.
TitleState::TitleState() = default;

void TitleState::Enter()
{
	cout << "Entering TitleState..." << endl;
	TEMA::Load("../Assets/img/Title.png", "title");
	TEMA::Load("../Assets/img/button.png", "play");
	TEMA::Load("../Assets/img/TitleBack.jpg", "bg");
	
	SOMA::Load("../Assets/aud/Title.mp3", "title", SOUND_MUSIC);
	SOMA::AllocateChannels(16);
	SOMA::SetMusicVolume(32);
	SOMA::PlayMusic("title", -1, 2000);

	AddChild("bg", new Image({ 0, 0, 1920, 1200 }, { 0.0f, 0.0f, 1024.0f, 768.0f }, "bg"));
	AddChild("title", new Image({ 0, 0, 800, 156 }, { 112.0f, 100.0f, 800.0f, 156.0f }, "title"));
	AddChild("play", new PlayButton({ 0, 0, 400, 100 }, { 412.0f, 384.0f, 200.0f, 50.0f }, "play"));
}

void TitleState::Update()
{
	State::Update();
}

void TitleState::Render()
{
	SDL_SetRenderDrawColor(REMA::GetRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(REMA::GetRenderer());
	State::Render();
}

void TitleState::Exit()
{
	cout << "Exiting TitleState..." << endl;
	TEMA::Unload("title");
	TEMA::Unload("play");
	TEMA::Unload("bg");
	SOMA::StopMusic();
	SOMA::Unload("title", SOUND_MUSIC);
	State::Exit();
}
// End TitleState.

// Begin PauseState.
PauseState::PauseState() = default;

void PauseState::Enter()
{
	cout << "Entering PauseState..." << endl;
}

void PauseState::Update()
{
	if (EVMA::KeyPressed(SDL_SCANCODE_R))
	{
		STMA::PopState();
		return;
	}
	State::Update();
}

void PauseState::Render()
{
	// First render the GameState
	STMA::GetStates().front()->Render();
	// Now render rest of PauseState
	SDL_SetRenderDrawBlendMode(REMA::GetRenderer(), SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(REMA::GetRenderer(), 0, 0, 255, 128);
	SDL_Rect rect = { 256, 128, 512, 512 };
	SDL_RenderFillRect(REMA::GetRenderer(), &rect);
	State::Render();
}

void PauseState::Exit()
{
	cout << "Exiting PauseState..." << endl;
	State::Exit();
}
// End PauseState.

// Begin GameState.
GameState::GameState() = default;

void GameState::Enter()
{
	cout << "Entering GameState..." << endl;
	TEMA::Load("../Assets/img/background.png", "bg");
	TEMA::Load("../Assets/img/Sprites.png", "sprites");
	SOMA::Load("../Assets/aud/Engines.wav", "engines", SOUND_SFX);
	SOMA::Load("../Assets/aud/Fire.wav", "fire", SOUND_SFX);
	SOMA::Load("../Assets/aud/Explode.wav", "explode", SOUND_SFX);
	SOMA::Load("../Assets/aud/Teleport.wav", "teleport", SOUND_SFX);
	SOMA::Load("../Assets/aud/Wings.mp3", "wings", SOUND_MUSIC);
	SOMA::SetSoundVolume(16);
	SOMA::SetMusicVolume(32);
	SOMA::PlayMusic("wings", -1, 2000);

	AddChild("bg", new Image({ 0, 0, 1024, 768 }, { 0, 0, 1024, 768 }, "bg"));
	AddChild("bullets", new BulletPool());
	AddChild("ship", new Ship({ 0, 0, 100, 100 }, { 462.0f, 334.0f, 100.0f, 100.0f }));
	AddChild("field", new AsteroidField(8));
}

void GameState::Update()
{
	if (EVMA::KeyPressed(SDL_SCANCODE_X))
	{
		STMA::ChangeState(new TitleState()); // Change to new TitleState
		return;
	}
	else if (EVMA::KeyPressed(SDL_SCANCODE_P))
	{
		STMA::PushState(new PauseState()); // Add new PauseState
		return;
	}
	// Check collision.
	vector<Asteroid*>& field = static_cast<AsteroidField*>(GetChild("field"))->GetAsteroids();
Ship* ship = static_cast<Ship*>(GetChild("ship"));
// Collision of ship and asteroids.
if (ship != nullptr)
{
	for (unsigned int i = 0; i < field.size(); i++)
	{
		Asteroid* ast = field.at(i);
		if (COMA::CircleCircleCheck(ship->GetCenter(), ast->GetCenter(),
			ship->GetRadius(), ast->GetRadius()))
		{
			SOMA::PlaySound("explode");
			RemoveChild("ship");
		}
	}
}
// Collision of bullets and asteroids.
vector<Bullet*>& bullets = static_cast<BulletPool*>(GetChild("bullets"))->GetBullets();
for (unsigned int i = 0; i < bullets.size(); i++)
{
	Bullet* bul = bullets.at(i);
	for (unsigned int j = 0; j < field.size(); j++)
	{
		Asteroid* asteroid = field.at(j);
		if (COMA::CircleCircleCheck(bul->GetCenter(), asteroid->GetCenter(),
			bul->GetRadius(), asteroid->GetRadius()))
		{
			const short asteroidSize = asteroid->GetSize();
			if (asteroidSize <= 0) {
				return;
			}
			const short debrisSize = asteroidSize - 1;
			for (int i = 0; i < 2; ++i) {
				const int delta = (i == 0) ? ((rand() % 15) + 30) : -((rand() % 15) + 30);
				auto debris = new Asteroid({ 510, 0, 60, 70 },
					{ asteroid->GetDst()->x, asteroid->GetDst()->y, asteroid->GetDst()->w - 15, asteroid->GetDst()->h - 15 });
				debris->UpdateDeltas(bul->GetAngle() + delta);
				const auto colour = asteroid->GetColMods();
				debris->SetColMods(colour[0], colour[1], colour[2]);
				debris->SetSize(debrisSize);
				field.push_back(debris);
			}
			// End new asteroid block.
			SOMA::PlaySound("explode");
			bul->SetEnabled(false);
			asteroid->SetEnabled(false);
			goto end;
		}
	}
}
end:
	State::Update();
}

void GameState::Render()
{
	SDL_SetRenderDrawColor(REMA::GetRenderer(), 0, 0, 255, 255);
	SDL_RenderClear(REMA::GetRenderer());
	State::Render();
}

void GameState::Exit()
{
	cout << "Exiting GameState..." << endl;
	TEMA::Unload("bg");
	TEMA::Unload("sprites");
	SOMA::StopSound();
	SOMA::StopMusic();
	SOMA::Unload("engines", SOUND_SFX);
	SOMA::Unload("fire", SOUND_SFX);
	SOMA::Unload("explode", SOUND_SFX);
	SOMA::Unload("teleport", SOUND_SFX);
	SOMA::Unload("wings", SOUND_MUSIC);
	State::Exit();
}

void GameState::Resume()
{
	cout << "Resuming GameState..." << endl;
}
// End GameState