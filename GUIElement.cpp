#include "GUIElement.h"

#include "AttatchedPosition.h"

GUIElement::GUIElement(int x, int y, Position &otherPos, int sizeX, int sizeY, std::string imagePath) :
	Sprite(
		*new AttatchedPosition(x, y, otherPos),
		sizeX,
		sizeY, 
		imagePath)
{}


GUIElement::~GUIElement() {}

void GUIElement::render(SDL_Renderer * renderer) {
}
