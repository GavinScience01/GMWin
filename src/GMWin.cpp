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
		if (!(*it)->active) return;
		(*it)->render();
	}
}

void GMWin::Update() {
	std::vector<GMWindow*>* windows = GMStorage::getInstance().getWindowStack();
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (GMStorage::getInstance().getSelected() != nullptr) {
			if (GMStorage::getInstance().getSelected() == nullptr) return;
			GMStorage::getInstance().getSelected()->update(e);
		}

		if (e.type == SDL_MOUSEBUTTONDOWN) {
			for (std::vector<GMWindow*>::reverse_iterator it = windows->rbegin(); it != windows->rend(); it++) {
				GMWindow* window = *it;
				if (!window->active) return;
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
		GMStorage::getInstance().setCurrentWindow(window);
	}
}

void GMWin::End() {
	GMStorage::getInstance().endWindow();
}


//WINDOW SETTINGS
void GMWin::SetTransparent(bool transparent) {
	GMWindow* window = GMStorage::getInstance().currentWindow();
	if (window == nullptr) return;
	window->transparent = transparent;
}


//COMPONENT ADDING
void GMWin::Text(std::string label, const char* name, int x, int y) {
	GMWindow* window = GMStorage::getInstance().currentWindow();
	if (window == nullptr) return;
	if (window->getComponent(name) == nullptr) {
		GMTextComponent* comp = new GMTextComponent(x, y + window->nextY, name, label);
		window->addComponent(comp);
	}
}

void GMWin::Check(bool* checked, std::string label, const char* name, int x, int y) {
	GMWindow* window = GMStorage::getInstance().currentWindow();
	if (window == nullptr) return;
	if (window->getComponent(name) == nullptr) {
		GMCheckComponent* comp = new GMCheckComponent(x, y + window->nextY, name, checked, label);
		window->addComponent(comp);
	}
}

void GMWin::FloatMatrix(float** grid, int sizeX, int sizeY, std::string label, const char* name, int x, int y) {
	GMWindow* window = GMStorage::getInstance().currentWindow();
	if (window == nullptr) return;
	if (window->getComponent(name) == nullptr) {
		GMFloatGridComponent* comp = new GMFloatGridComponent(x, y + window->nextY, name, grid, sizeX, sizeY, label);
		window->addComponent(comp);
	}
}

void GMWin::DynamicText(std::string* pLabel, const char* name, int x, int y) {
	GMWindow* window = GMStorage::getInstance().currentWindow();
	if (window == nullptr) return;
	if (window->getComponent(name) == nullptr) {
		GMDynamicTextComponent* comp = new GMDynamicTextComponent(x, y + window->nextY, name, pLabel);
		window->addComponent(comp);
	}
}

bool GMWin::Button(std::string buttonText, std::string label, const char* name, int x, int y) {
	GMWindow* window = GMStorage::getInstance().currentWindow();
	if (window == nullptr) return false;
	GMButtonComponent* comp = (GMButtonComponent*)(window->getComponent(name));
	if (comp == nullptr) {
		GMButtonComponent* comp = new GMButtonComponent(x, y + window->nextY, name, buttonText, label);
		window->addComponent(comp);
		return false;
	}
	else {
		return comp->clicked;
	}
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
void GMWin::TestingWindow(std::string* pLabel, bool* checked) {
	GMWin::Begin("Testing Window");
	GMWin::Text("Hello World!", "hi");
	GMWin::Check(checked, "This is a checkbox", "check");
	GMWin::DynamicText(pLabel, "height");
	if (GMWin::Button("Quit", " ", "quit")) {
		SDL_DestroyWindow(GMStorage::getInstance().getWindow());
		SDL_DestroyRenderer(GMStorage::getInstance().getRenderer());
		SDL_Quit();
	}
	GMWin::End();
}