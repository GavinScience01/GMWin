#include "GMWin.h"
#include "GMWindow.h"
#include "GMStorage.h"

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
		for (std::vector<GMWindow*>::iterator it = windows->begin(); it != windows->end(); it++) {
			(*it)->update(e);
		}
	}
	GMStorage::getInstance().remove();
}

//WINDOW HANDLING
void GMWin::Init(SDL_Renderer* renderer) {
	GMStorage::getInstance().setRenderer(renderer);
	GMUtils::setColor(255, 255, 255, 255);
}

void GMWin::Begin(const char* title, GMWindowFlags flags) {
	GMWindow* window = new GMWindow(title, flags);
	GMStorage::getInstance().pushWindow(window);
}

void GMWin::End() {
	GMStorage::getInstance().endWindow();
}

//COMPONENT ADDING
void GMWin::AddText(std::string label, const char* name, int x, int y) {
	GMWindow* window = GMStorage::getInstance().currentWindow();
	GMTextComponent* comp = new GMTextComponent(x, y + window->nextY, name, label);
	window->addComponent(comp);
}

void GMWin::AddCheck(bool checked, std::string label, const char* name, int x, int y) {
	GMWindow* window = GMStorage::getInstance().currentWindow();
	GMCheckComponent* comp = new GMCheckComponent(x, y + window->nextY, name, checked, label);
	window->addComponent(comp);
}

void GMWin::AddFloatMatrix(float** grid, int sizeX, int sizeY, std::string label, const char* name, int x, int y) {
	GMWindow* window = GMStorage::getInstance().currentWindow();
	GMFloatGridComponent* comp = new GMFloatGridComponent(x, y + window->nextY, name, grid, sizeX, sizeY, label);
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
void GMWin::TestingWindow() {
	float** grid = new float*[2];
	for (int i = 0; i < 2; i++) {
		grid[i] = new float[2];
		grid[i][0] = .25;
		grid[i][1] = .5;
	}


	GMWin::Begin("Testing Window");
	GMWin::AddText("Hello World!", "hi");
	GMWin::AddCheck(false, "This is a checkbox", "check");
	GMWin::AddFloatMatrix(grid, 2, 2, "MNIST Mini", "mnist");
	GMWin::End();
}