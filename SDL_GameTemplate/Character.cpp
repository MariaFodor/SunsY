#include "Character.h"
#include"Game.h"//for the touched matrx
#include "TextureManager.h"
#include<iostream>
using namespace std;
Character::Character(const char* path, SDL_Renderer* renderer) : renderer(renderer)
{
	setTex(path);
}

void Character::setTex(const char* path)
{
	texture = TextureManager::LoadTexture(path, renderer);
}


void Character::init(int a, int b,int lvl,Map* map)
{
	srcRect.x = srcRect.y = 0;
	srcRect.w = 66;
	srcRect.h = 40;
	destRect.w = 66;
	destRect.h = 40;//the size of the character on the screen
	
	destRect.x = a;//the initial poossition on the screen
	destRect.y = b;


	//The velocity of the dot
	mVelX = 0;
	mVelY = 0;
	this->lvl = lvl;
	this->m = map;
	p=m->GetWall(lvl);//setarea zonelor inaccesibila pt move
}



void Character::move(bool mat[20][25], int lvl)
{
	int VelX = *getVelX();
	int VelY = *getVelY();
	destRect.x += VelX;
	destRect.y += VelY;
	//daca avem coleziune sau se iese din ecran

	{
		bool coleziune = 0;
		bool coleziune_finish = 0;
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
			//Move back
			destRect.x -= VelX;
		}
		//If the character collided or went too far up or down
		if ((destRect.y < 0) || (destRect.y + destRect.h > SCREEN_HEIGHT) || coleziune)
		{
			//Move back
			destRect.y -= VelY;
		}
	}
}
bool Character::checkCollision(SDL_Rect a, SDL_Rect b, bool mat[20][25])
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	//cout << endl << "COLEZIUNE!!";
	int j = b.x / 32;
	int i = b.y / 32;
	mat[i][j] = 1;//we mark the fact that a wall was touched 
	return true;

}
void Character::free_gameinfo(void)
{
	delete[] p;
	p = nullptr;
}
void Character::draw()
{
	TextureManager::Draw(texture, srcRect, destRect, renderer);
}
bool Character::checkCollision_2rect(SDL_Rect a, SDL_Rect b)//for enemyes and finishline check
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	return true;

}

