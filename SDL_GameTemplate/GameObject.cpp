#include "GameObject.h"
#include "TextureManager.h"
#include <SDL.h>

GameObject::GameObject(const char* textureSheet, SDL_Renderer* renderer, int x, int y)
{
   _renderer = renderer;
   _texture = TextureManager::LoadTexture(textureSheet, _renderer);
   _x = x;
   _y = y;
}

GameObject::~GameObject() = default;

void GameObject::Update() {//aici scriem ce face obiectul
	_x++;
	_y++;

	_srcRectangle.h = 32;
	_srcRectangle.w = 32;
	_srcRectangle.x = 0;
	_srcRectangle.y = 0;

	_destRectangle.x = _x;
	_destRectangle.y = _y;
	_destRectangle.w = 32;
	_destRectangle.h = 32;//dimensiunile raman egale dar se modifica pozitia
}

void GameObject::Render()
{
	SDL_RenderCopy(_renderer, _texture, nullptr, &_destRectangle);
}