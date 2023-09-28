#include "GMComponent.h"

#include "GMUtils.h"

//COMPONENT
GMComponent::GMComponent(int x, int y, const char* name) {
	this->x = x;
	this->y = y;
	this->name = name;
	this->width = 0;
	this->height = 0;
}


//TEXT
GMTextComponent::GMTextComponent(int x, int y, const char* name, std::string label) : GMComponent(x, y, name) {
	this->label = label;
	this->width = label.size() * 8;
	this->height = 13;
}

void GMTextComponent::render(int xOffset, int yOffset) {
	GMUtils::renderText(label.c_str(), x + xOffset, y + yOffset);
}


//CHECKBOX
GMCheckComponent::GMCheckComponent(int x, int y, const char* name, bool* checked, std::string label) : GMComponent(x, y, name) {
	this->checked = checked;
	this->label = label;
	this->width = 40 + label.size() * 8;
	this->height = 30;
}

void GMCheckComponent::render(int xOffset, int yOffset) {
	GMUtils::setColor(20, 40, 70, 255);
	GMUtils::renderRect(x + xOffset, y + yOffset, 30, 30);
	GMUtils::renderText(label.c_str(), x + xOffset + 40, y + yOffset + 10);

	if (*checked) {
		GMUtils::renderImage(x + xOffset + 5, y + yOffset + 5, 20, 20, "images/check.bmp");
	}
}

//TODO: migrate this so not all components have to calculate position
void GMCheckComponent::update(SDL_Event e, int xOffset, int yOffset) {
	if (e.type == SDL_MOUSEBUTTONDOWN) {
		int rx = e.button.x - xOffset;
		int ry = e.button.y - yOffset;

		if (rx >= GMUtils::COMP_PADDING && rx <= 30 + GMUtils::COMP_PADDING && ry >= GMUtils::COMP_PADDING && ry <= 30 + GMUtils::COMP_PADDING) {
			*checked = !(*checked);
		}
	}
}


//FLOAT MATRIX
GMFloatGridComponent::GMFloatGridComponent(int x, int y, const char* name, float** grid, int sizeX, int sizeY, std::string label) : GMComponent(x, y, name) {
	this->grid = grid;
	this->label = label;
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	this->width = (sizeX * 20) + 10 + label.size() * 8;
	this->height = 20 * sizeY;
}

void GMFloatGridComponent::render(int xOffset, int yOffset) {
	for (int j = 0; j < sizeY; j++) {
		for (int i = 0; i < sizeX; i++) {
			float f = grid[i][j];
			GMUtils::setColor(f * 255, f * 255, f * 255, 255);
			GMUtils::renderRect((i * 20) + x + xOffset, (j * 20) + y + yOffset, 20, 20);
		}
	}
	GMUtils::renderText(label.c_str(), x + xOffset + (sizeX * 20) + 10, y + yOffset + (sizeY * 10) - 7);
}


//DYNAMIC TEXT
GMDynamicTextComponent::GMDynamicTextComponent(int x, int y, const char* name, std::string* pLabel) : GMComponent(x, y, name) {
	this->pLabel = pLabel;
	this->height = 13;
}

void GMDynamicTextComponent::render(int xOffset, int yOffset) {
	GMUtils::renderText(pLabel->c_str(), x + xOffset, y + yOffset);
	//needs to be adjusted based on text updates
	this->width = pLabel->size() * 8;
}


//BUTTON
//due to limits brought up by passing a function, may shift components to being returned and added in between frames
GMButtonComponent::GMButtonComponent(int x, int y, const char* name, std::string buttonText, std::string label) : GMComponent(x, y, name) {
	this->buttonText = buttonText;
	this->label = label;
	this->width = 40 + (buttonText.size() * 8) + 10 + (label.size() * 8);
	this->height = 30;
	this->clicked = false;
	this->hover = false;
}

void GMButtonComponent::render(int xOffset, int yOffset) {
	if (hover) {
		GMUtils::setColor(10, 20, 50, 255);
	}
	else {
		GMUtils::setColor(20, 40, 70, 255);
	}
	GMUtils::renderRect(x + xOffset, y + yOffset, width - (label.size() * 8), 30);
	GMUtils::renderText(buttonText.c_str(), x + xOffset + 20, y + yOffset + 7);
	GMUtils::renderText(label.c_str(), width - (label.size() * 8), y + yOffset);
}

void GMButtonComponent::update(SDL_Event e, int xOffset, int yOffset) {
	clicked = false;
	if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN) {
		int rx = e.button.x - xOffset;
		int ry = e.button.y - yOffset;

		if (rx >= GMUtils::COMP_PADDING && rx <= width - (label.size() * 8) + GMUtils::COMP_PADDING && ry >= GMUtils::COMP_PADDING && ry <= 30 + GMUtils::COMP_PADDING) {
			this->hover = true;
			if (e.type == SDL_MOUSEBUTTONDOWN && clicked == false) {
				clicked = true;
				printf("hi");
			}
			else {
				clicked = false;
			}
		}
		else {
			hover = false;
		}
	}
}