#include <SDL.h>
#include <iostream>

#include "GMWin.h"
#include "GMStorage.h"

int main(int argc, char* args[]) {
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return -1;
	}
	if (TTF_Init() < 0) {
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", SDL_GetError());
		return -1;
	}
	
	SDL_Renderer* renderer;
	SDL_Window* window;

	SDL_CreateWindowAndRenderer(800, 800, SDL_WINDOW_OPENGL, &window, &renderer);

	GMWin::Init(renderer);
	GMWin::TestingWindow();
	GMWin::TestingWindow();

	while (1) {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		GMWin::Render();
		SDL_RenderPresent(renderer);
	}
		

	//Destroy window
	SDL_DestroyWindow(window);

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}
