#pragma once
#include <SDL_image.h>

class Map
{
public:
	Map(SDL_Renderer* renderer,int lvl);
	~Map();

	void LoadMap(int arr[20][25]);
	void DrawMap(bool mat[20][25]);

	//adugam:
	SDL_Rect* GetWall(int lvl);
	SDL_Rect* GetFinish(int lvl);//doua finctii foarte asemanatoare

private:
	//SDL_Rect finish;//va fi punctul in care daca ajunge primul castiga
	SDL_Renderer* renderer;
	SDL_Rect src, dest;
	SDL_Texture* Finish;
	SDL_Texture* wall;

	friend class Player;
	friend class Enemy;
	

	int map[20][25];//mapa propriu zisa sub forma de matrice
};

void load_maps();