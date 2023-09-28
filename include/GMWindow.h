#pragma once

#include "GMWin.h"
#include "GMUtils.h"
#include "GMComponent.h"

class GMWindow {
public:

	GMWindow(const char* title, GMWindowFlags flags);
	~GMWindow();

	const char* title;
	GMWindowFlags flags;
	int posX, posY;
	int sizeX, sizeY, prevSize;
	bool condensed;
	bool transparent;
	bool active;
	//for components
	int nextY;

	void render();
	void update(const SDL_Event& e);

	void addComponent(GMComponent* comp);
	void removeComponent(GMComponent* comp);
	GMComponent* getComponent(const char* name);

	void setPos(int posX, int posY);
	void setSize(int sizeX, int sizeY);

	bool inWindowBar(int x, int y);
	bool inGrabber(int x, int y);
	bool inCondenser(int x, int y);
	bool inCloser(int x, int y);

private:
	std::vector<GMComponent*> components;
	GMComponent* selected;

	void mouseEvent(const SDL_MouseMotionEvent& e);
	void clickEvent(const SDL_MouseButtonEvent& e);
	void keyboardEvent(const SDL_KeyboardEvent& e);
	void scrollEvent(const SDL_MouseWheelEvent& e);
	void textEvent(const SDL_TextInputEvent& e);
};