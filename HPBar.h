#pragma once
#include "GUIElement.h"

class HPBar : public GUIElement {
private:
	int w;
	int h;
	SDL_Color bgColor;
	SDL_Color fgColor;
public:
	HPBar(int x, int y, Position &otherPos, int sizeX, int sizeY, std::string imagePath, int w, int h, SDL_Color fgColor, SDL_Color bgColor);
	~HPBar();

	void render(SDL_Renderer *renderer);
};

