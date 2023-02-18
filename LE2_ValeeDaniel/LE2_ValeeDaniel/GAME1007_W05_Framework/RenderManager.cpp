#include "RenderManager.h"
#include <iostream>

int RenderManager::Init(const char* title, const int xPos, const int yPos,
	const int width, const int height, const Uint32 wFlags, const Uint32 rFlags)
{
	m_pWindow = SDL_CreateWindow(title, xPos, yPos, width, height, wFlags);
	if (m_pWindow == nullptr)
	{
		std::cout << "Error during window creation!" << std::endl;
		return 1;
	}
	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, rFlags);
	if (m_pRenderer == nullptr)
	{
		std::cout << "Error during renderer creation!" << std::endl;
		return 1;
	}
	return 0; // All good.
}

void RenderManager::Quit()
{
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
}

RenderManager& RenderManager::Instance()
{
	static RenderManager instance; // Magic statics. Creating the object.
	return instance;
}

SDL_Renderer* RenderManager::GetRenderer()
{
	return m_pRenderer;
}

SDL_Window* RenderManager::GetWindow()
{
	return m_pWindow;
}
