#pragma once
#include "SDL_image.h"

class GameObject
{
public:
	GameObject(const char* textureSheet, SDL_Renderer* renderer, int x, int y);
	~GameObject();

	void Update();
	void Render();

private:
	int _x;//xpos
	int _y;//tops
	SDL_Texture* _texture;//texture
	SDL_Rect _srcRectangle;//sursa
	SDL_Rect _destRectangle;//cred ca unde il pune
	SDL_Renderer* _renderer;
};