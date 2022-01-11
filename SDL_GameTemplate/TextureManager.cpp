#include "TextureManager.h"
#include <SDL.h>
#include <SDL_image.h>

SDL_Texture* TextureManager::LoadTexture(const char* fileName, SDL_Renderer* renderer)
{
	SDL_Surface* tempSurface = IMG_Load(fileName);//create surface fileName=texture
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tempSurface);//se creaza o trexura din suprafata
	SDL_FreeSurface(tempSurface);
	return tex;
}

void TextureManager::Draw(SDL_Texture * tex, SDL_Rect src, SDL_Rect dest, SDL_Renderer* renderer)
{
   // sent with nullptr
	SDL_RenderCopy(renderer, tex, nullptr, &dest);//&source eeste ous null ptr
}
