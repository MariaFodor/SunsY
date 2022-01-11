#include "Game.h"
#include "Map.h"
#include "Player.h"
#include"TextureManager.h"

Map* map;
Player* player;
Enemy* enemy;

//declarati pt single player
Enemy* enemy11;
Enemy* enemy12;
Enemy* enemy13;
Enemy* enemy22;
Enemy* enemy23;
Enemy* enemy21;
Enemy* enemy31;
Enemy* enemy32;
Enemy* enemy33;





bool touched[20][25];//declar matricea



int mm;//map multiplayer

SDL_Event Game::event;
Game::Game() : isRunning(false), renderer(nullptr),playerDeath(false),mainMenu(true),game_type(false),map_selection(false),
map_selection_multiplayer(false), single_1(false),single_2(false),single_3(false),two_players(false),help_flag(false){};//initializez cu mainMenu(true)

Game::~Game()
{
   delete player;
   delete enemy;
}


void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	music = PlaySoundA("assets/in_my_way.wav", NULL, SND_LOOP | SND_ASYNC);
	load_maps();//load maps info ftom data.txt file
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;//face fullscreen sau nu in functie de flagul plasat ca atgument in SDL_createWindow
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems initialized" << std::endl;//outout consola...sisteme initializate
		auto window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window!=nullptr)
		{
			std::cout << "Window created" << std::endl;
		}
 
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer != nullptr)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255,255);//culoare render ului
			std::cout << "Renderer created" << std::endl;
		}
		isRunning = true;
	}
	else
	{
		isRunning = false;
	}
	
	{
		help= TextureManager::LoadTexture("assets/help.png", renderer);
		main_menu = TextureManager::LoadTexture("assets/meniu.png", renderer);
		pink_won = TextureManager::LoadTexture("assets/pink_wins.png", renderer);
		yellow_won = TextureManager::LoadTexture("assets/yellow_wins.png", renderer);
		backgroud = TextureManager::LoadTexture("assets/pink_sky.png", renderer);
		gameType = TextureManager::LoadTexture("assets/game_type.png", renderer);
		mapSel= TextureManager::LoadTexture("assets/lvl_selection.png", renderer);//paint first
		mapSel_mult= TextureManager::LoadTexture("assets/map_multi.png", renderer);
		//map = new Map(renderer,1);
		enemy = new Enemy("assets/pink.png", renderer);
		enemy11= new Enemy("assets/pink.png", renderer);
		enemy12= new Enemy("assets/pink.png", renderer);
		enemy13= new Enemy("assets/pink.png", renderer);
		enemy21 = new Enemy("assets/pink.png", renderer);
		enemy22 = new Enemy("assets/pink.png", renderer);
		enemy23 = new Enemy("assets/pink.png", renderer);
		enemy31 = new Enemy("assets/pink.png", renderer);
		enemy32 = new Enemy("assets/pink.png", renderer);
		enemy33 = new Enemy("assets/pink.png", renderer);
		player = new Player("assets/clo.png", renderer);
	}
}

typedef struct rectangle {
	int x;
	int y;
	int w;
	int h;
	rectangle(int x, int y, int z, int k) {
		this->x = x; this->y = y; this->w = (z-x); this->h = (k-y);}
	bool contains(int a, int b) { return (x <= a) && (a <= x + w) && (y <= b) && (b <= y + h);}

};

void Game::handleEvents()
{
	rectangle rectangle_1 = rectangle(293, 152, 555, 214);//casuta 1
	rectangle rectangle_2 = rectangle(293, 244, 555, 294);//casuta 2
	rectangle rectangle_3 = rectangle(293, 332, 557, 384);//casuta 3
	while (SDL_PollEvent(&event) != 0)
	{
		if (mainMenu)
		{
			erase_seen_walls();
			clear_ginfo();
			playerDeath = 0;
			playerWon = 0;
			switch (event.type)
			{
			case SDL_MOUSEBUTTONDOWN: {
				int x;
				int y;
				SDL_GetMouseState(&x, &y);
				//cout << "Coordonatele mousului sunt (" << x << ". " << y << ")\n";
				if (rectangle_1.contains(x, y)) {
					mainMenu = false;
					game_type = true;
				}
				if (rectangle_2.contains(x, y))
				{
					if (music) { PlaySound(NULL, NULL, 0); music = 0; }
					else
					{
						music = PlaySoundA("assets/in_my_way.wav", NULL, SND_LOOP | SND_ASYNC);

					}
					break;
				}
				if (rectangle_3.contains(x, y))
				{
					isRunning = false;
				}
				break;
			}
			case SDL_QUIT: {
				isRunning = false;
				break;
			}
			case SDL_KEYDOWN:
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_h:
				{
					mainMenu = false;
					help_flag = true;
					break;
				}
				case SDLK_s:
				{
					mainMenu = false;
					game_type = true;
					break;
				}
				case SDLK_m:
				{
					if (music) { PlaySound(NULL, NULL, 0); music = 0; }
					else
					{
						music = PlaySoundA("assets/in_my_way.wav", NULL, SND_LOOP | SND_ASYNC);
						
					}
					break;
				}
				case SDLK_e:
				{
					isRunning = false;
					break;
				}
				default:
				{
					break;
				}
				}
			}
			}
		}
		else
		{
			if (game_on)
			{
				switch (event.type)
				{
				case SDL_QUIT:
				{
					isRunning = false;
					break;
				}
				default:
				{
					if (player->IsDead() || player->hasWon())
					{
						if (player->IsDead()) {
							playerDeath = 1;
						}
						if (player->hasWon()) { playerWon = 1; }
						game_on = 0;
					}
					player->handele_events(event);
					if(two_players)
					{ 
					enemy->handele_events(event);
					}
					break;
				}
				}

			}

			else
			{
				if (playerDeath || playerWon)
				{
					switch (event.key.keysym.sym)
					{
					case SDLK_RETURN:
						two_players = 0;
						single_1 = 0;
						single_2 = 0;
						single_3 = 0;
						mainMenu = 1;
						break;
					}
				}
				if (game_type)
				{
					switch (event.type)
					{
						case SDL_MOUSEBUTTONDOWN: 
						{
							int x;
							int y;
							SDL_GetMouseState(&x, &y);
							//cout << "Coordonatele mousului sunt (" << x << ". " << y << ")\n";
							if (rectangle_1.contains(x, y)) {
								game_type = false;
								map_selection_multiplayer = true;
							}
							if (rectangle_2.contains(x, y))
							{
								game_type = false;
								map_selection = true;
							}
							if (rectangle_3.contains(x, y))
							{
								game_type = false;
								mainMenu = true;
							}
							break;
						}
						case SDL_QUIT:
						{
							isRunning = false;
							break;
						}
					}
				}
				else
				{
					if (map_selection)
					{
						int press = 0;
						switch (event.type)
						{
							case(SDL_MOUSEBUTTONDOWN):
							{
								int x; int y;
								SDL_GetMouseState(&x, &y);
								if (rectangle_1.contains(x, y)) {
									single_1 = 1;
									player->init(0, 0,4,map);
									enemy11->init(0 * 32, 8 * 32 - 2 * 8,4,map);
									enemy12->init(23 * 32 - 10, 17 * 32 + 10,4,map);
									enemy13->init(11 * 32, 0 * 32,4,map);
									press = 1;
								}
								if (rectangle_2.contains(x, y))
								{
									single_2 = 1;
									player->init(0, 0,5,map);
									enemy21->init(17 * 32, 11 * 32,5,map);
									enemy22->init(22 * 32, 3 * 32,5,map);
									press = 2;
								}
								if (rectangle_3.contains(x, y))
								{
									single_3 = 1;
									player->init(11 * 32, 8 * 32 + 16,6,map);
									enemy31->init(22 * 32, 2 * 32,6,map);
									enemy32->init(19 * 32, 17 * 32,6,map);
									enemy33->init(32 * 12.75, 32 * 0,6,map);
									press = 3;
								}
								if (press)
								{
									map = choose_map(0, press);
									map_selection = 0;
									game_on = 1;
								}
									break;
							}
							case SDL_QUIT:
							{
								isRunning = false;
								break;
							}
						}
					}

					else
					{
						if (map_selection_multiplayer)
						{
							int press = 0;
							switch (event.type)
							{
							case SDL_MOUSEBUTTONDOWN:
							{
								int x;
								int y;
								SDL_GetMouseState(&x, &y);
								if (rectangle_1.contains(x, y)) {
									player->init(22*32, 0*32,1,map);
									enemy->init(0*32, 18*32,1,map);
									mm = 1;
									press = 1;
								}
								if (rectangle_2.contains(x, y))
								{
									player->init(0, 11 * 32,2,map);
									enemy->init(0, 15 * 32,2,map);
									mm = 2;
									press = 2;
								}
								if (rectangle_3.contains(x, y))
								{
									player->init(22 * 32, 11 * 32,3,map);
									enemy->init(0 * 32, 11 * 32,3,map);
									mm = 3;
									press = 3;
								}
								if (press)
								{
									map = choose_map(1, press);
									erase_seen_walls();
									map_selection_multiplayer = 0;
									two_players = 1;//flag for the type of control on enemy
									game_on = 1;
								}
								break;
							}
							case SDL_QUIT:
							{
								isRunning = false;
								break;
							}
							}
						}
						else
						{
							if (help_flag)
							{
								switch (event.key.keysym.sym)
								{
								case SDLK_RETURN:
									two_players = 0;
									single_1 = 0;
									single_2 = 0;
									single_3 = 0;
									mainMenu = 1;
									break;
								}
							}
						}
					}
				}
			}



		}
	}
}
	
	

void Game::update() 
{

	if (two_players)
	{
		player->Player_vel = 4;
		enemy->Player_vel = 4;
		player->move( touched, *enemy,mm);//mm tells the map we are on
		enemy->move(touched,mm);
	}
	if (single_1)
	{
		player->Player_vel = 1;
		player->move( touched, *enemy13, 4);
		player->move( touched, *enemy11,4);
		player->move( touched, *enemy12,4);
		enemy11->move_auto(touched,0,4);
		enemy12->move_auto( touched, 0,4);
		enemy13->move_auto( touched, 1, 4);
	}
	if (single_2)
	{
		player->Player_vel = 2;
		player->move( touched, *enemy21,5);
		player->move(touched, *enemy22,5);
		enemy21->move_auto( touched, 0,5);
		enemy22->move_auto(touched, 0,5);
	}
	if (single_3)
	{
	
		player->Player_vel = 1;
		player->move( touched, *enemy31,6);
		player->move( touched, *enemy32, 6);
		player->move( touched, *enemy33, 6);
		enemy31->move_auto( touched, 0,6);
		enemy32->move_auto(touched, 1, 6);
		enemy33->move_auto( touched, 1, 6);
	}
	
}

void Game::render() const
{
	SDL_RenderClear(renderer);
	TextureManager tex_select;
	if (game_on)
	{
		SDL_RenderCopy(renderer, backgroud, NULL, NULL);//background default
		map->DrawMap(touched);//map in top of default background
		player->draw();
		if (two_players) 
		{
		enemy->draw();
		}
		if (single_1)
		{
			enemy11->draw();
			enemy12->draw();
			enemy13->draw();
		}
		if (single_2)
		{
			enemy21->draw();
			enemy22->draw();
			enemy23->draw();
		}
		if (single_3)
		{
			enemy31->draw();
			enemy32->draw();
			enemy33->draw();
		}

	}
	else
	{
		if (mainMenu)
		{
			SDL_RenderCopy(renderer, main_menu, NULL, NULL);
		}
		else
		{
			if (playerDeath)
			{
				SDL_RenderCopy(renderer, pink_won, NULL, NULL);

			}
			else
			{
				if (playerWon)//if yellow won
				{
					SDL_RenderCopy(renderer, yellow_won, NULL, NULL);
				}
				else
				{
					if (game_type)
					{
						SDL_RenderCopy(renderer, gameType, NULL, NULL);
					}
					else
					{
						if (map_selection_multiplayer)
						{
							SDL_RenderCopy(renderer, mapSel_mult, NULL, NULL);
						}
						else
						{
							if (map_selection)
							{
								SDL_RenderCopy(renderer, mapSel, NULL, NULL);
							}
							else
							{
								if (help_flag)
								{
									SDL_RenderCopy(renderer, help, NULL, NULL);
								}
							}
						}
					}
				}
			}
		}
	}
	SDL_RenderPresent(renderer);
}

void Game::clean() const
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_QUIT;
}
void Game::erase_seen_walls()
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			touched[i][j] = 0;
		}
	}
}
Map* Game::choose_map(bool type,int press)//ca reintoarce o mapa in functie de tipul jocului si butonul apasat;0-2 playeri 1-un player
{
	Map* map = 0;
	if (type)//daca jucam multiplayer
	{
		switch (press)
		{
		case 1:
			map = new Map(renderer, 1);
			break;
		case 2:
			map = new Map(renderer, 2);
			break;
		case 3:
			map = new Map(renderer, 3);
			break;
		default:
			break;
		}
	}
	else//SINGLE
	{
		switch (press)
		{
		case 1:
			map = new Map(renderer, 4);
			break;
		case 2:
			map = new Map(renderer, 5);
			break;
		case 3:
			map = new Map(renderer, 6);
			break;
		default:
			break;
		}
	}
	return map;
}
void Game::clear_ginfo(void)//for going back to main menu
{
	player->free_gameinfo();
	enemy->free_gameinfo();
}