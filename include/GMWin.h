#pragma once

#include <SDL.h>
#include <string>
#include "GMUtils.h"

typedef int GMWindowFlags;

enum GMWindowFlags_ {
	GMWindowFlags_None = 0,
	GMWindowFlags_NoMove = 1 << 0,
	GMWindowFlags_NoTitle = 1 << 1,
};

namespace GMWin {

	void Init(SDL_Window* window, SDL_Renderer* renderer);
	void Begin(const char* title, GMWindowFlags flags = 0);
	void End();

	void Render();
	void Update();

	void SetTransparent(bool transparent);

	void Text(std::string label, const char* name, int x = 0, int y = 0);
	void Check(bool* checked, std::string label, const char* name, int x = 0, int y = 0);
	void FloatMatrix(float** grid, int sizeX, int sizeY, std::string label, const char* name, int x = 0, int y = 0);
	void DynamicText(std::string* pLabel, const char* name, int x = 0, int y = 0);
	bool Button(std::string buttonText, std::string label, const char* name, int x = 0, int y = 0);

	void setPos(int posX, int posY);
	void setSize(int sizeX, int sizeY);

	void TestingWindow(std::string* pLabel, bool* checked);

}