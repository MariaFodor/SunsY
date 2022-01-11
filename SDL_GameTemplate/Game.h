#pragma once
#include <SDL.h>
#include <Windows.h>
#include<mmsystem.h>//cele 2 pentru muzica
#include "Player.h"
#include"Enemy.h"
#include <iostream>
using namespace std;
//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 640;

class Game
{
public:
	Game();
	~Game();
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void update(); //const;
	void render() const;
	void clean() const;
	static SDL_Event event;
	bool running() const { return isRunning;  }//intreaba daca e running
	bool new_game()const { return mainMenu; }//intreaba daca vrea un joc nou
	void erase_seen_walls();
	Map* choose_map(bool type, int press);
private:
	static int exit;
	int cnt=0;

	bool isRunning;
	bool playerDeath;
	bool playerWon;
	bool mainMenu;
	bool game_type;
	bool map_selection;
	bool map_selection_multiplayer;
	bool game_on;
	bool help_flag;
	bool music;

	//setam flaguri pentru configurarea inamicului
	bool single_1;
	bool single_2;
	bool single_3;//sele 3 nivele de single game

	bool two_players;//multipllayer


	SDL_Window* window;
	SDL_Renderer* renderer;

	SDL_Texture* yellow_won;
	SDL_Texture* pink_won;//vor fi dezactivate la un enter sau ceva

	SDL_Texture* gameType;
	SDL_Texture* mapSel;
	SDL_Texture* mapSel_mult;
	SDL_Texture* help;

	SDL_Texture* main_menu;//meniul de stra
	SDL_Texture* backgroud;//adaugata de  mine

	void clear_ginfo(void);//informatiile de revenire la main menu
};
