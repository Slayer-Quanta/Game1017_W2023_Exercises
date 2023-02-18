#ifndef __RENDERMANAGER_H__
#define __RENDERMANAGER_H__
#include <SDL.h>

class RenderManager
{
public: // Public methods.
	int Init(const char*, const int, const int, const int, const int, const Uint32, const Uint32);
	void Quit();
	static RenderManager& Instance(); // Static method for object access.
	SDL_Renderer* GetRenderer();
	SDL_Window* GetWindow(); // Just in case this is ever needed.

private: // Private properties.
	SDL_Window* m_pWindow; 
	SDL_Renderer* m_pRenderer;
	RenderManager() = default;
};

typedef RenderManager REMA;

#endif