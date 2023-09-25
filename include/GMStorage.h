#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>

#include "GMWindow.h"

class GMStorage {
public:
	static GMStorage& getInstance() {
		static GMStorage instance;
		return instance;
	}
private:
	GMStorage();
	
public:
	GMStorage(GMStorage const&) = delete;
	void operator=(GMStorage const&) = delete;

	void setRenderer(SDL_Renderer* renderer);
	SDL_Renderer* getRenderer();

	void pushWindow(GMWindow* window);
	GMWindow* getWindow(const char* title);
	GMWindow* currentWindow();
	std::vector<GMWindow*>* getWindowStack();
	void endWindow();
	void queueRemove(GMWindow* win);
	void updateStacks();

	bool getMousePressed();
	void setMousePressed(bool pressed);

	TTF_Font* getFont();
	void changeFontSize(int size);

	void selectWindow(GMWindow* selected);
	GMWindow* getSelected();

	void setWindow(SDL_Window* window);
	SDL_Window* getWindow();
	
private:
	std::vector<GMWindow*> windowStack;
	std::vector<GMWindow*> deleteStack;
	SDL_Renderer* renderer;
	SDL_Window* sdlWindow;
	GMWindow* window;
	GMWindow* selected;
	bool mousePressed;
	TTF_Font* font;
};