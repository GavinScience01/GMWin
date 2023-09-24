#pragma once

#include <vector>
#include <SDL.h>
#include <SDL_ttf.h>

namespace GMUtils {

	void setColor(int r, int g, int b, int a);

	void renderLine(int x1, int y1, int x2, int y2);
	void renderRect(int x, int y, int w, int h);
	void renderTriangle(float x1, float y1, float x2, float y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void renderText(const char* text, int x, int y);

	double triArea(int x1, int y1, int x2, int y2, int x3, int y3);
};
