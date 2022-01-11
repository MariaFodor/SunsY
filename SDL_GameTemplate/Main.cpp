//Using SDL and standard IO

#include "Game.h"
#include <SDL.h>

using namespace std;

int main(int argc, char* args[])
{
	bool start_game = 0;
	const int fps = 60;
	// max time between frames
	SDL_Window* window;//declar un singur window
	
	const int frameDelay = 1000 / fps;//maxtime berween frames
	
		Game* game = new Game();
			game->init("Sunsy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false);

			while (game->running())//while gime is running
			{
				Uint32 frameStart = SDL_GetTicks();

				game->handleEvents();//handele game inputs
				game->update();
				game->render();//generate image
				const int frameTime = SDL_GetTicks() - frameStart;

				if (frameDelay > frameTime)
				{
					SDL_Delay(frameDelay - frameTime);
				}
			}
		game->clean();
		delete game;
	
	return 0;
}