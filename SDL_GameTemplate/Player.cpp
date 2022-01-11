#include"Game.h"
#include "Map.h"
#include "Player.h"
#include "TextureManager.h"
#include<iostream>
using namespace std;
Player::Player(const char* path, SDL_Renderer* renderer) :Character(path, renderer) {};

void Player::init(int x, int y,int lvl,Map*map)
{
	Character::init(x, y,lvl,map);
	this->finish = map->GetFinish(lvl);
	dead = 0;
	win = 0;
}
bool Player::IsDead()
{
	return dead;
}
bool Player::hasWon()
{
	return win;
}
void Player::handele_events(SDL_Event& e)
{
	int* VelX = getVelX();
	int* VelY = getVelY();
	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//we change the velocyty
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: *VelY -= Player_vel; break;
		case SDLK_DOWN:*VelY += Player_vel; break;
		case SDLK_LEFT: *VelX -= Player_vel; break;
		case SDLK_RIGHT: *VelX += Player_vel; break;
		}
	}
	//If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//we change the welocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: *VelY += Player_vel; break;
		case SDLK_DOWN: *VelY -= Player_vel; break;
		case SDLK_LEFT: *VelX += Player_vel; break;
		case SDLK_RIGHT:*VelX -= Player_vel; break;
		}
	}

}
void Player::free_gameinfo(void)
{
	delete[]finish;
	finish = 0;
}
void Player::move(bool mat[20][25],Enemy e,int lvl)
{
	Character::move(mat, lvl);
	 for (int i = 0; i < 20; i++)
	 {
		 if (checkCollision_2rect(destRect, finish[i]))//game won by yellow
		 {
			 win = 1;
		 }
	 }
	if (checkCollision_2rect(destRect,e.return_enemy()))//game lost by yellow
	{
		dead = 1;
	}

}
