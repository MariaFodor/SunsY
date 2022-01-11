#pragma once
#include "Map.h"
#include "Enemy.h"
#include "Character.h"
#include "SDL.h"

class Player : public Character
{
	bool dead;
	bool win;
	SDL_Rect* finish;
public:
	Player(const char* path, SDL_Renderer* renderer);

	void init(int x, int y,int lvl,Map*map) override;

	void handele_events(SDL_Event& e);

	void move(bool mat[20][25],Enemy e,int lvl);//primeste ca parametru mapa si ia fiecare dreptunchi din mapa in parte

	bool IsDead();

	void free_gameinfo(void);

	bool hasWon();
	
};
