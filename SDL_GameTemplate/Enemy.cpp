#include"Game.h"
#include "Enemy.h"
#include "TextureManager.h"
#include<iostream>
using namespace std;
SDL_Rect Enemy::return_enemy()
{
	return destRect;
}
Enemy::Enemy(const char* path, SDL_Renderer* renderer) :Character(path, renderer) {};

void Enemy::move( bool mat[20][25], int lvl)
{
	Character::move(mat, lvl);

}

void Enemy::handele_events(SDL_Event& e)
{
	int* VelX = getVelX();
	int* VelY = getVelY();
	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Adjust the velocity
			//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_w: *VelY -= Player_vel;break;
		case SDLK_s:*VelY += Player_vel; break;
		case SDLK_a: *VelX -= Player_vel; break;
		case SDLK_d: *VelX += Player_vel; break;
		}
	}
	//If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_w: *VelY += Player_vel; break;
		case SDLK_s: *VelY -= Player_vel; break;
		case SDLK_a: *VelX += Player_vel; break;
		case SDLK_d:*VelX -= Player_vel; break;
		}
	}

}
void Enemy::move_auto(bool mat[20][25],int dir,int lvl)//int dir will decide it it moves along x ot y axis
{
	if (dir == 0)
	{
		destRect.x += Enemy_vel_auto;
		{
			bool coleziune = 0;
			int i = 0;
			while (p[i].h != 0)
			{
				if (checkCollision(destRect, p[i], mat))
				{
					coleziune = checkCollision(destRect, p[i], mat);
				}
				i++;
			}
			if ((destRect.x < 0) || (destRect.x + destRect.w > SCREEN_WIDTH) || coleziune)
			{
				Enemy_vel_auto = (-1) * Enemy_vel_auto;
			}
		}

	}
	if (dir == 1)
	{
		destRect.y += Enemy_vel_auto;
		{
			bool coleziune = 0;
			int i = 0;
			while (p[i].h != 0)
			{
				if (checkCollision(destRect, p[i], mat))
				{
					coleziune = checkCollision(destRect, p[i], mat);
				}
				i++;
			}
			if ((destRect.y < 0) || (destRect.y + destRect.h > SCREEN_HEIGHT) || coleziune)
			{
				Enemy_vel_auto = (-1) * Enemy_vel_auto;
			}
		}

	}
}
