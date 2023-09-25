#pragma once

#include <vector>
#include <SDL.h>
#include <SDL_ttf.h>

namespace GMUtils {

	int constexpr BAR_DEPTH = 22;
	int constexpr GRABBER_SIZE = 30;

	int constexpr COMP_PADDING = 10;

	void setColor(int r, int g, int b, int a);

	void renderLine(int x1, int y1, int x2, int y2);
	void renderRect(int x, int y, int w, int h);
	void renderTriangle(float x1, float y1, float x2, float y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void renderText(const char* text, int x, int y);
	void renderImage(int x, int y, int w, int h, const char* file);

	double triArea(int x1, int y1, int x2, int y2, int x3, int y3);
};
