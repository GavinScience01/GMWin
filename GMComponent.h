#pragma once

#include <vector>
#include <string>
#include <SDL.h>

class GMComponent {
public:
	GMComponent(int x, int y, const char* name);
	int x, y;
	int width, height;
	const char* name;

	virtual void render(int xOffset, int yOffset)=0;
private:
	SDL_Renderer* renderer;
};

class GMSuperComponent : public GMComponent {
public:
	std::vector<GMComponent> components;
	int heightBias;
};

class GMTextComponent : public GMComponent {
public:
	GMTextComponent(int x, int y, const char* name, std::string text);
	std::string label;
	void render(int xOffset, int yOffset);
};