#include "GMWindow.h"

#include <iostream>
#include <cmath>

#include "GMStorage.h"

GMWindow::GMWindow(const char* title, GMWindowFlags flags) {
	this->title = title;
	this->flags = flags;
	posX = 50;
	posY = 50;
	sizeX = 300;
	sizeY = 200;
	condensed = false;
	transparent = false;
	active = true;

	nextY = GMUtils::BAR_DEPTH + GMUtils::COMP_PADDING;
}

GMWindow::~GMWindow() {
	for (GMComponent* comp : components) {
		delete comp;
	}
	delete[] &components;
}

void GMWindow::render() {
	//TODO: add scroll bars and clipping for too many components

	//window
	GMUtils::setColor(0, 10, 50, 255);
	if (!transparent) {
		GMUtils::renderRect(posX, posY + GMUtils::BAR_DEPTH, sizeX, sizeY - GMUtils::BAR_DEPTH);
	}
	else {
		GMUtils::renderLineRect(posX, posY + GMUtils::BAR_DEPTH, sizeX, sizeY - GMUtils::BAR_DEPTH);
	}

	//grab bar, only visible if not condensed
	//TODO: change hover color
	if (!condensed) {
		GMUtils::renderTriangle(posX + sizeX - GMUtils::GRABBER_SIZE, posY + sizeY, posX + sizeX, posY + sizeY - GMUtils::GRABBER_SIZE, 30, 60, 90, 255);
	}

	//window bar
	GMUtils::setColor(25, 75, 150, 255);
	GMUtils::renderRect(posX, posY, sizeX, GMUtils::BAR_DEPTH);
	GMUtils::renderText(title, posX+25, posY+4);

	//arrow, add lerp to closing? may be too slow
	//math a bit weird, adds nice condensed effect
	int a;
	int b;
	if (condensed) {
		a = 14;
		b = 8;
	}
	else {
		a = 8;
		b = 14;
	}
	GMUtils::renderTriangle(posX + a, posY + b, posX + b, posY + a, 255, 255, 255, 255);

	//close, mostly random ish until I got the size right
	GMUtils::setColor(255, 255, 255, 255);
	GMUtils::renderLine(posX + sizeX - 6, posY + 6, posX + sizeX - GMUtils::BAR_DEPTH + 6, posY + GMUtils::BAR_DEPTH - 6);
	GMUtils::renderLine(posX + sizeX - 6, posY + GMUtils::BAR_DEPTH - 6, posX + sizeX - GMUtils::BAR_DEPTH + 6, posY + 6);

	//render comps, adds a slight x bias
	//currently stops rendering when a component doesn't fit in the window, will be changed to create a scroll
	if (!condensed) {
		int height = GMUtils::BAR_DEPTH;
		for (GMComponent* comp : components) {
			height += comp->height + GMUtils::COMP_PADDING;
			if (sizeY >= height && sizeX >= comp->width + GMUtils::COMP_PADDING) {
				comp->render(posX + GMUtils::COMP_PADDING, posY);
			}
		}
	}
}

void GMWindow::update(const SDL_Event& e) {
	if (e.type == SDL_MOUSEMOTION) {
		mouseEvent(e.motion);
	}
	else if (e.type == SDL_KEYDOWN) {
		keyboardEvent(e.key);
	}
	else if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
		clickEvent(e.button);
	}
	else if (e.type == SDL_MOUSEWHEEL) {
		scrollEvent(e.wheel);
	}
	else if (e.type == SDL_TEXTINPUT) {
		textEvent(e.text);
	}

	for (GMComponent* comp : components) {
		comp->update(e, posX, posY + comp->y - GMUtils::COMP_PADDING);
	}
}

void GMWindow::mouseEvent(const SDL_MouseMotionEvent& e) {
	if (GMStorage::getInstance().getMousePressed()) {
		if (inWindowBar(e.x, e.y)) {
			int w;
			int h;
			SDL_GetWindowSize(GMStorage::getInstance().getWindow(), &w, &h);

			if (posX + e.xrel >= 0 && posX + e.xrel <= w - GMUtils::BAR_DEPTH) {
				posX += e.xrel;
			}
			if (posY + e.yrel >= 0 && posY + e.yrel <= h - GMUtils::BAR_DEPTH) {
				posY += e.yrel;
			}
		}
		else if (inGrabber(e.x, e.y)) {
			if (sizeX + e.xrel > GMUtils::GRABBER_SIZE) {
				sizeX += e.xrel;
			}
			else {
				posX += e.xrel;
			}
			sizeY += e.yrel;
		}
	}
}

void GMWindow::clickEvent(const SDL_MouseButtonEvent& e) {
	if (e.button == SDL_BUTTON_LEFT) {
		GMStorage::getInstance().setMousePressed(e.state == SDL_PRESSED);
		if (e.state != SDL_PRESSED) return;
		if (inCondenser(e.x, e.y)) {
			if (condensed) {
				condensed = false;
				sizeY = prevSize;
			}
			else {
				condensed = true;
				prevSize = sizeY;
				sizeY = GMUtils::BAR_DEPTH;
			}
		}
		else if (inCloser(e.x, e.y)) {
			GMStorage::getInstance().queueRemove(this);
			delete this;
		}
	}
}

void GMWindow::keyboardEvent(const SDL_KeyboardEvent& e) {
	
}

void GMWindow::scrollEvent(const SDL_MouseWheelEvent& e) {

}

void GMWindow::textEvent(const SDL_TextInputEvent& e) {

}

void GMWindow::addComponent(GMComponent* comp) {
	components.push_back(comp);
	nextY += comp->height + GMUtils::COMP_PADDING;
}

void GMWindow::removeComponent(GMComponent* comp) {
	//currently inactive, add a queue if necessary
}

GMComponent* GMWindow::getComponent(const char* name) {
	for (int i = 0; i < components.size(); i++) {
		if (components[i]->name == name) {
			return components[i];
		}
	}
	return nullptr;
}

void GMWindow::setPos(int x, int y) {
	posX = x;
	posY = y;
}

void GMWindow::setSize(int x, int y) {
	sizeX = x;
	sizeY = y;
}

bool GMWindow::inWindowBar(int x, int y) {
	int rx = x - posX;
	int ry = y - posY;
	return (rx >= 0 && rx <= sizeX) && (ry >= 0 && ry <= GMUtils::BAR_DEPTH);
}

bool GMWindow::inGrabber(int x, int y) {
	//way harder than rect collision ik...
	//TODO: make this general triangle collision and move to GMUtils maybe?
	int rx = x - posX;
	int ry = y - posY;

	int x1 = sizeX - GMUtils::GRABBER_SIZE;
	int y1 = sizeY;
	int x2 = sizeX;
	int y2 = sizeY - GMUtils::GRABBER_SIZE;
	int x3 = sizeX;
	int y3 = sizeY;
	float grabArea = GMUtils::triArea(x1, y1, x2, y2, x3, y3);

	//calculate area of triangle PBC
	float a1 = GMUtils::triArea(rx, ry, x2, y2, x3, y3);

	//calculate area of triangle PAC
	float a2 = GMUtils::triArea(x1, y1, rx, ry, x3, y3);

	//calculate area of triangle PAB
	float a3 = GMUtils::triArea(x1, y1, x2, y2, rx, ry);

	return grabArea == (a1 + a2 + a3);
}

bool GMWindow::inCondenser(int x, int y) {
	int rx = x - posX;
	int ry = y - posY;

	return (rx >= 0 && rx <= 16) && (ry >= 0 && ry <= 16);
}

bool GMWindow::inCloser(int x, int y) {
	int rx = x - posX;
	int ry = y - posY;

	return (rx >= sizeX - GMUtils::BAR_DEPTH && rx <= sizeX) && (ry >= 0 && ry <= GMUtils::BAR_DEPTH);
}