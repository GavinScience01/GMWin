#include "GMUtils.h"

#include "GMWindow.h"
#include "GMStorage.h"

///<summary>
///Sets the current renderer color
///</summary>
void GMUtils::setColor(int r, int g, int b, int a) {
	SDL_SetRenderDrawColor(GMStorage::getInstance().getRenderer(), r, g, b, a);
}

void GMUtils::setColor(SDL_Color color) {
	SDL_SetRenderDrawColor(GMStorage::getInstance().getRenderer(), color.r, color.g, color.b, color.a);
}

///<summary>
///Draws a line (bruh what else)
///</summary>
void GMUtils::renderLine(int x1, int y1, int x2, int y2) {
	SDL_RenderDrawLine(GMStorage::getInstance().getRenderer(), x1, y1, x2, y2);
}

///<summary>
///Draws rect using current renderer
///</summary>
void GMUtils::renderRect(int x, int y, int w, int h) {
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	SDL_RenderFillRect(GMStorage::getInstance().getRenderer(), &rect);
}

///<summary>
///Draws line rect using current renderer
///</summary>
void GMUtils::renderLineRect(int x, int y, int w, int h) {
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	SDL_RenderDrawRect(GMStorage::getInstance().getRenderer(), &rect);
}

///<summary>
///Draws a right triangle using the inputs as a hypotenuse, with the first being the bottom and last being the top (flip for inverted)
///</summary>
void GMUtils::renderTriangle(float x1, float y1, float x2, float y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	SDL_Vertex vertex1 = { {x1, y1},{r, g, b, a}, {1, 1} };
	SDL_Vertex vertex2 = { {x2, y2},{r, g, b, a}, {1, 1} };
	SDL_Vertex vertex3 = { {x2, y1},{r, g, b, a}, {1, 1} };

	SDL_Vertex vertices[] = {
		vertex1,
		vertex2,
		vertex3
	};

	SDL_RenderGeometry(GMStorage::getInstance().getRenderer(), NULL, vertices, 3, NULL, 0);
}

///<summary>
///Draws the given text to the xy coordinates
///</summary>
void GMUtils::renderText(const char* text, int x, int y) {
	if (text == "") return;

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(GMStorage::getInstance().getFont(), text, { 255, 255, 255 });
	SDL_Texture* message = SDL_CreateTextureFromSurface(GMStorage::getInstance().getRenderer(), surfaceMessage);
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = surfaceMessage->w;
	rect.h = surfaceMessage->h;

	SDL_RenderCopy(GMStorage::getInstance().getRenderer(), message, NULL, &rect);
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(message);
}

///<summary>
///Draws an image at the file location to the xy coordinates
///</summary>
void GMUtils::renderImage(int x, int y, int w, int h, const char* file) {
	SDL_Surface* image = SDL_LoadBMP(file);
	if (image == NULL) {
		printf("Unable to load image! SDL Error: %s\n", SDL_GetError());
	}

	SDL_Texture* imageTex = SDL_CreateTextureFromSurface(GMStorage::getInstance().getRenderer(), image);
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	SDL_RenderCopy(GMStorage::getInstance().getRenderer(), imageTex, NULL, &rect);
	SDL_FreeSurface(image);
	SDL_DestroyTexture(imageTex);
}

///<summary>
///Calculates the area of a rectangle
///</summary>
double GMUtils::triArea(int x1, int y1, int x2, int y2, int x3, int y3) {
	return abs((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0);
}