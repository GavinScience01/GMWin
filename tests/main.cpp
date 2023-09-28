#include <SDL.h>
#include <iostream>
#include <string>

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

	std::string label;
	label = "Current Y Size:";
	bool checked;

	GMWin::Init(window, renderer);

	while (1) {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		//black rect for window transparency tests
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_Rect rect;
		rect.x = 400;
		rect.y = 400;
		rect.w = 200;
		rect.h = 200;
		SDL_RenderFillRect(renderer, &rect);

		GMWin::TestingWindow(&label, &checked);

		if (GMStorage::getInstance().getWindow("Testing Window") != nullptr) {
			label = "Current Y Size: " + std::to_string(GMStorage::getInstance().getWindow("Testing Window")->sizeY);
		}

		GMWin::Render();
		SDL_RenderPresent(renderer);
	}

	//Destroy window
	SDL_DestroyWindow(window);

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}
