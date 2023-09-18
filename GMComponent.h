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
	std::string label;

	virtual void render(int xOffset, int yOffset)=0;
};

class GMSuperComponent : public GMComponent {
public:
	std::vector<GMComponent> components;
	int heightBias;
};

class GMTextComponent : public GMComponent {
public:
	GMTextComponent(int x, int y, const char* name, std::string label);
	void render(int xOffset, int yOffset);
};

class GMCheckComponent : public GMComponent {
public:
	GMCheckComponent(int x, int y, const char* name, bool checked, std::string label);
	bool checked;
	void render(int xOffset, int yOffset);
};

class GMFloatGridComponent : public GMComponent {
public:
	GMFloatGridComponent(int x, int y, const char* name, float** grid, int sizeX, int sizeY, std::string label);
	float** grid;
	int sizeX;
	int sizeY;
	void render(int xOffset, int yOffset);
};