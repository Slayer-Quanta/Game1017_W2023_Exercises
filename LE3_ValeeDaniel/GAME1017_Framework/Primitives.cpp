#include "Primitives.h"
#include "RenderManager.h"
#include "TextureManager.h"

Image::Image(SDL_Rect src, SDL_FRect dst, const char* k) :Sprite(src, dst), m_key(k) {}

void Image::Render()
{
	SDL_RenderCopyF(REMA::GetRenderer(), TEMA::GetTexture(m_key), &m_src, &m_dst);
}

Line::Line(SDL_FPoint start, SDL_FPoint end, SDL_Color col) :
	GameObject({ 0,0,0,0 }), m_start(start), m_end(end), m_color(col) {}

void Line::Render()
{
	SDL_SetRenderDrawColor(REMA::GetRenderer(), m_color.r, m_color.g, m_color.b, m_color.a);
	SDL_RenderDrawLineF(REMA::GetRenderer(), m_start.x, m_start.y, m_end.x, m_end.y);
}

Rectangle::Rectangle(SDL_FRect dst, bool fill, SDL_Color col) :
	GameObject(dst), m_fill(fill), m_color(col) {}

void Rectangle::Render()
{
	SDL_SetRenderDrawColor(REMA::GetRenderer(), m_color.r, m_color.g, m_color.b, m_color.a);
	if (m_fill)
		SDL_RenderFillRectF(REMA::GetRenderer(), &m_dst);
	else
		SDL_RenderDrawRectF(REMA::GetRenderer(), &m_dst);
}
