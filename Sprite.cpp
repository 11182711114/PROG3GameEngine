#include "Sprite.h"
#include <iostream>
#include "Position.h"

void Sprite::init(SDL_Renderer *ren) {

	if (ren != NULL && imagePath != "") {

		SDL_Surface* surf = SDL_LoadBMP(imagePath.c_str());
		texture = SDL_CreateTextureFromSurface(ren, surf);

		SDL_FreeSurface(surf);
	}
}

void Sprite::tick(std::list<Sprite*> otherObj) {}

void Sprite::render(SDL_Renderer *renderer) {
	SDL_Rect rect = { pos.getPositionXAsInt(), pos.getPositionYAsInt(), sizeX, sizeY };
	//std::cout << "rendering: " << spr->getPath() << " @ x: " << spr->getPositionX() << " y: " << spr->getPositionY() << " sizeX: " << spr->getSizeX() << " sizeY: " << spr->getSizeY() << std::endl;
	if (SDL_RenderCopy(renderer, texture, NULL, &rect) != 0)
		std::cout << "error: " << SDL_GetError() << std::endl;
}

Sprite::Sprite(Position pos, int sizeX, int sizeY, std::string imagePath) :
	pos(pos),
	sizeX(sizeX),
	sizeY(sizeY),
	imagePath(imagePath) 
{}

Sprite::Sprite(int x, int y, int sizeX, int sizeY, std::string imagePath) :
	pos(*new Position(x, y)),
	sizeX(sizeX),
	sizeY(sizeY),
	imagePath(imagePath) 
{}

Sprite::~Sprite() {
	if (texture != NULL)
		SDL_DestroyTexture(texture);
}
