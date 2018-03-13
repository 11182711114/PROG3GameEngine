#ifndef GUIELEMENT_H
#define GUIELEMENT_H

#include "Sprite.h"
#include <SDL.h>

class GUIElement : public Sprite{
private:
public:
	GUIElement(int x, int y, Position &otherPos, int sizeX, int sizeY, std::string imagePath);
	~GUIElement();

	void render(SDL_Renderer *renderer);
};
#endif