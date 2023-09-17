#include "GMComponent.h"

#include "GMUtils.h"

//Component
GMComponent::GMComponent(int x, int y, const char* name) {
	this->x = x;
	this->y = y;
	this->name = name;
	this->width = 0;
	this->height = 0;
}

//Text
GMTextComponent::GMTextComponent(int x, int y, const char* name, std::string label) : GMComponent(x, y, name) {
	this->label = label;
}

void GMTextComponent::render(int xOffset, int yOffset) {
	GMUtils::renderText(label.c_str(), x + xOffset, y + yOffset);
}