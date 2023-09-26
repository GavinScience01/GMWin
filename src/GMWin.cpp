#include "GMWin.h"
#include "GMWindow.h"
#include "GMStorage.h"

#include <iostream>

//RENDERING AND UPDATING
///<summary>
///Renders all windows, no need for update call
///</summary>
void GMWin::Render() {
	Update();
	std::vector<GMWindow*>* windows = GMStorage::getInstance().getWindowStack();
	for (std::vector<GMWindow*>::iterator it = windows->begin(); it != windows->end(); it++) {
		(*it)->render();
	}
}

void GMWin::Update() {
	std::vector<GMWindow*>* windows = GMStorage::getInstance().getWindowStack();
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (GMStorage::getInstance().getSelected() != nullptr) {
			GMStorage::getInstance().getSelected()->update(e);
		}

		if (e.type == SDL_MOUSEBUTTONDOWN) {
			for (std::vector<GMWindow*>::reverse_iterator it = windows->rbegin(); it != windows->rend(); it++) {
				GMWindow* window = *it;
				int x = e.button.x - window->posX;
				int y = e.button.y - window->posY;

				if ((x >= 0 && x <= window->sizeX) && (y >= 0 && y <= window->sizeY)) {
					GMStorage::getInstance().selectWindow(window);
					GMStorage::getInstance().updateStacks();
					return;
				}
			}
		}
		/*for (std::vector<GMWindow*>::iterator it = windows->begin(); it != windows->end(); it++) {
			(*it)->update(e);
		}*/
	}
	GMStorage::getInstance().updateStacks();
}


//WINDOW HANDLING
void GMWin::Init(SDL_Window* window, SDL_Renderer* renderer) {
	GMStorage::getInstance().setRenderer(renderer);
	GMStorage::getInstance().setWindow(window);
	GMUtils::setColor(255, 255, 255, 255);
}

void GMWin::Begin(const char* title, GMWindowFlags flags) {
	GMWindow* window = GMStorage::getInstance().getWindow(title);
	if (window == nullptr) {
		GMWindow* w = new GMWindow(title, flags);
		GMStorage::getInstance().pushWindow(w);
	}
	else {
		GMStorage::getInstance().selectWindow(window);
	}
}

void GMWin::End() {
	GMStorage::getInstance().endWindow();
}


//WINDOW SETTINGS
void GMWin::SetTransparent(bool transparent) {
	GMWindow* window = GMStorage::getInstance().currentWindow();
	window->transparent = transparent;
}


//COMPONENT ADDING
void GMWin::AddText(std::string label, const char* name, int x, int y) {
	GMWindow* window = GMStorage::getInstance().currentWindow();
	GMTextComponent* comp = new GMTextComponent(x, y + window->nextY, name, label);
	window->addComponent(comp);
}

void GMWin::AddCheck(bool* checked, std::string label, const char* name, int x, int y) {
	GMWindow* window = GMStorage::getInstance().currentWindow();
	GMCheckComponent* comp = new GMCheckComponent(x, y + window->nextY, name, checked, label);
	window->addComponent(comp);
}

void GMWin::AddFloatMatrix(float** grid, int sizeX, int sizeY, std::string label, const char* name, int x, int y) {
	GMWindow* window = GMStorage::getInstance().currentWindow();
	GMFloatGridComponent* comp = new GMFloatGridComponent(x, y + window->nextY, name, grid, sizeX, sizeY, label);
	window->addComponent(comp);
}

void GMWin::AddDynamicText(std::string* pLabel, const char* name, int x, int y) {
	GMWindow* window = GMStorage::getInstance().currentWindow();
	GMDynamicTextComponent* comp = new GMDynamicTextComponent(x, y + window->nextY, name, pLabel);
	window->addComponent(comp);
}

void GMWin::AddButton(std::string buttonText, std::string label, const char* name, int x, int y) {
	GMWindow* window = GMStorage::getInstance().currentWindow();
	GMButtonComponent* comp = new GMButtonComponent(x, y + window->nextY, name, buttonText, label);
	window->addComponent(comp);
}


//VARIABLE CHANGING
void GMWin::setPos(int x, int y) {
	GMStorage::getInstance().currentWindow()->posX = x;
	GMStorage::getInstance().currentWindow()->posY = y;
}

void GMWin::setSize(int x, int y) {
	GMStorage::getInstance().currentWindow()->sizeX = x;
	GMStorage::getInstance().currentWindow()->sizeY = y;
}


//TEST WINDOWS
void GMWin::TestingWindow(std::string* pLabel) {
	float** grid = new float*[2];
	for (int i = 0; i < 2; i++) {
		grid[i] = new float[2];
		grid[i][0] = .25;
		grid[i][1] = .5;
	}

	bool checked;

	GMWin::Begin("Testing Window");
	GMWin::AddText("Hello World!", "hi");
	GMWin::AddCheck(&checked, "This is a checkbox", "check");
	GMWin::AddFloatMatrix(grid, 2, 2, "MNIST Mini", "mnist");
	GMWin::AddDynamicText(pLabel, "height");
	GMWin::AddButton("Quit", " ", "quit");
	GMWin::End();
}