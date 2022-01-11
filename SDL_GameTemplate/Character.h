
#pragma once
#include "Map.h"
#include "Component.h"
#include "SDL.h"
#include<iostream>
using namespace std;
class Character : public Component
{

	SDL_Texture* texture{};
	SDL_Renderer* renderer{};
	

	//The velocity of the dot
	int mVelX = 0;
	int mVelY = 0;//modificarea care a stricat

	int lvl=0;//a vector of innaccesible possitions for every lvl
	Map* m=nullptr;//pointer to the chosen map
public:
	SDL_Rect* p = nullptr;//a vecor of walls(in the form of SDL_Rect type)
	SDL_Rect srcRect{}, destRect{};
	//access mathods
	inline int* getVelY() { int* p; p = &mVelY; return p; };
	inline int* getVelX() { int* p; p = &mVelX; return p; };

	Character() = default;
	Character(const char* path, SDL_Renderer* renderer);
	~Character(void)
	{
		texture = 0;
		delete texture;
		renderer = 0;
		delete renderer;
	}
	int Player_vel = 0;
	void setTex(const char* path);

	virtual void init(int x, int y,int lvl,Map*map) override;

	void draw() override;

	bool checkCollision(SDL_Rect a, SDL_Rect b, bool mat[20][25]);

	virtual void handele_events(SDL_Event& e)=0;//wasd for enemy; arrows for player

	void move( bool mat[20][25], int lvl);

	bool checkCollision_2rect(SDL_Rect a, SDL_Rect b);

	void free_gameinfo(void);
};

