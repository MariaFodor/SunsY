#include "Map.h"
#include<iostream>
using namespace std;
#include "TextureManager.h"
#include <SDL.h>
#include <fstream>

//ifstream fin("data.txt");

int lvl1[20][25];
int lvl2[20][25];
int lvl3[20][25];
int lvl4[20][25];
int lvl5[20][25];
int lvl6[20][25];

void load_maps()
{
	ifstream fin("data.txt");

	try
	{
		if (!fin.is_open())
		{
			throw 90;
		}
		else
		{
			for (int i = 0; i < 20; i++)
				for (int j = 0; j < 25; j++)
					fin >> lvl1[i][j];

			for (int i = 0; i < 20; i++)
				for (int j = 0; j < 25; j++)
					fin >> lvl2[i][j];

			for (int i = 0; i < 20; i++)
				for (int j = 0; j < 25; j++)
					fin >> lvl3[i][j];

			for (int i = 0; i < 20; i++)
				for (int j = 0; j < 25; j++)
					fin >> lvl4[i][j];

			for (int i = 0; i < 20; i++)
				for (int j = 0; j < 25; j++)
					fin >> lvl5[i][j];

			for (int i = 0; i < 20; i++)
				for (int j = 0; j < 25; j++)
					fin >> lvl6[i][j];
		}
		
	}
	catch (int x) { std::cout << "Exception: The file containig map data did not open.\n"; }
	fin.close();
}


void coppy_matrix(int a[20][25], int b[20][25])
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			a[i][j] = b[i][j];
		}
	}
}


Map::Map(SDL_Renderer* renderer,int lvl)
{
	this->renderer = renderer;
	wall = TextureManager::LoadTexture("assets/deep_wall.png", renderer);
	Finish = TextureManager::LoadTexture("assets/yellow_wall2.png", renderer);
	switch(lvl)
	{
	case 1:
		LoadMap(lvl1);
		break;
	case 2:
		LoadMap(lvl2);
		break;
	case 3:
		LoadMap(lvl3);
		break;
	case 4:
		LoadMap(lvl4);
		break;
	case 5:
		LoadMap(lvl5);
		break;
	case 6:
		LoadMap(lvl6);
		break;

	default:
		break;
	}

	src.x = 0;
	src.y = 0;
	src.w = 32;
	src.h = 32;
	dest.x = 0;
	dest.y = 0;
	dest.w = 32;
	dest.h = 32;

}
SDL_Rect* Map::GetFinish(int lvl)
{
	SDL_Rect* finish = new SDL_Rect[20];//dimensiunea maxima a dreptunghiurilor de finish
	int p[20][25];
	switch (lvl)
	{
	case 1:
		coppy_matrix(p, lvl1);
		break;
	case 2:
		coppy_matrix(p, lvl2);
		break;
	case 3:
		coppy_matrix(p, lvl3);
		break;
	case 4:
		coppy_matrix(p, lvl4);
		break;
	case 5:
		coppy_matrix(p, lvl5);
		break;
	case 6:
		coppy_matrix(p, lvl6);
		break;
	default:
		break;
	}
	for (int i = 0; i < 20; i++)
	{
		finish[i].x = finish[i].y = finish[i].w = finish[i].h = 0;//aceasta va fi verificarea pentru cand se termins vectorul
	}
	int cont = 0;
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			if (p[i][j] == 2)
			{
				finish[cont].x = j * 32;//am inversat i cu j
				finish[cont].y = i * 32;
				finish[cont].h = 32;
				finish[cont].w = 32;//sper ca asta ia fiecare patratel in parte
				cont++;
				//std::cout << i<<" "<<j << std::endl;
			}
		}
	}
	return finish;//returneaza un vector cu zonele de finish
}
SDL_Rect* Map::GetWall(int lvl)//vom seta wall-ul d acum pe 1 in matrice
{
	//use global SDL_Rect inaccesible[500]; make 0 before use
	SDL_Rect* inaccesible = new SDL_Rect[500];//dimensiunea maxima a dreptunghiurilor inaccesibile
	int p[20][25];
	switch (lvl)
	{
	case 1:
		coppy_matrix(p, lvl1);
		break;
	case 2:
		coppy_matrix(p, lvl2);
		break;
	case 3:
		coppy_matrix(p, lvl3);
		break;
	case 4:
		coppy_matrix(p, lvl4);
		break;
	case 5:
		coppy_matrix(p, lvl5);
		break;
	case 6:
		coppy_matrix(p, lvl6);
		break;
	default:
		break;
	}
	for (int i = 0; i < 500; i++) 
	{
		inaccesible[i].x = inaccesible[i].y = inaccesible[i].w = inaccesible[i].h = 0;
	}
	int cont = 0;
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			if (p[i][j] == 1)
			{
				inaccesible[cont].x =j * 32;
				inaccesible[cont].y =i* 32;
				inaccesible[cont].h = 32;
				inaccesible[cont].w = 32;
				cont++;
			}
		}
	}
	return inaccesible;//returneaza un vector cu zonele inaccesibile
}

Map::~Map()
{
	delete[] map;
}

void Map::LoadMap(int arr[20][25])//alege unul dintre nivele
{
	for (int row = 0; row < 20; row++)
	{
		for (int column = 0; column < 25; column++)
		{
				map[row][column] = arr[row][column];
		}
	}
}

void Map::DrawMap(bool mat[20][25])//fac functia asta sa deseneze doar daca a fost detecteata colezinea
{
	int type = 0;
	for (int row = 0; row < 20; row++)
	{
		for (int column = 0; column < 25; column++)
		{
			type = map[row][column];

			dest.x = column * 32;
			dest.y = row * 32;
			switch (type)
			{
			case 0:
				//TextureManager::Draw(grass, src, dest, renderer);
				break;
			case 1:
			{if (mat[row][column]) {
				TextureManager::Draw(wall, src, dest, renderer);

			}}break;
			case 2:
				TextureManager::Draw(Finish, src, dest, renderer);
				//finish line ul
				break;
			
			default:
				break;

			}
		}
	}
}
