#include <iostream>
#include <algorithm>

#include "GMStorage.h"

GMStorage::GMStorage() {
	renderer = NULL;
	window = NULL;
	mousePressed = false;
	selected = nullptr;

	font = TTF_OpenFont("ProggyClean.ttf", 18);
	if (font == NULL) {
		printf("Font failed to load! SDL_ttf error: %s\n", TTF_GetError());
	}
}

SDL_Renderer* GMStorage::getRenderer() {
	return renderer;
}

void GMStorage::setRenderer(SDL_Renderer* renderer) {
	this->renderer = renderer;
}

void GMStorage::pushWindow(GMWindow* window) {
	windowStack.push_back(window);
	this->window = window;
	this->selected = window;
}

GMWindow* GMStorage::getWindow(const char* title) {
	for (GMWindow* window : windowStack) {
		if (window->title == title) {
			this->window = window;
			return window;
		}
	}
	return nullptr;
}

std::vector<GMWindow*>* GMStorage::getWindowStack() {
	return &windowStack;
}

GMWindow* GMStorage::currentWindow() {
	return window;
}

void GMStorage::endWindow() {
	window = nullptr;
}

void GMStorage::queueRemove(GMWindow* win) {
	deleteStack.push_back(win);
}

void GMStorage::updateStacks() {
	int index = deleteStack.size();
	while (deleteStack.size() > 0 && index >= 0) {
		for (int i = 0; i < windowStack.size(); i++) {
			if (windowStack[i] == deleteStack.back()) {
				windowStack.erase(windowStack.begin() + i);
				if (selected == deleteStack.back()) selected = nullptr;
				deleteStack.pop_back();
				index--;
				break;
			}
		}
	}
	deleteStack.clear();
	windowStack.shrink_to_fit();
}

bool GMStorage::getMousePressed() {
	return mousePressed;
}

void GMStorage::setMousePressed(bool pressed) {
	mousePressed = pressed;
}

TTF_Font* GMStorage::getFont() {
	return font;
}

void GMStorage::changeFontSize(int size) {
	font = TTF_OpenFont("slkscr.ttf", size);
	if (font == NULL) {
		printf("Font failed to load! SDL_ttf error: %s\n", TTF_GetError());
	}
}

void GMStorage::selectWindow(GMWindow* selected) {
	this->selected = selected;
	std::vector<GMWindow*>::iterator it = std::find(windowStack.begin(), windowStack.end(), selected);
	windowStack[it - windowStack.begin()] = windowStack.back();
	windowStack[windowStack.size() - 1] = selected;

}

GMWindow* GMStorage::getSelected() {
	return selected;
}