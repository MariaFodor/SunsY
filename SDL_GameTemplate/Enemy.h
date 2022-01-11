#pragma once
#include "Character.h"
#include <iostream>
using namespace std;
#include "Map.h"
#include "Component.h"
#include "SDL.h"

class Enemy : public Character
{
public:

	Enemy() = default;
	Enemy(const char* path, SDL_Renderer* renderer);

	void handele_events(SDL_Event& e);
	void move(bool mat[20][25], int lvl);

	int Enemy_vel_auto=2;

	void move_auto(bool mat[20][25], int dir,int lvl);//primeste doar o directie pe care sa se delaseze//metoda noua

	SDL_Rect return_enemy();
};

