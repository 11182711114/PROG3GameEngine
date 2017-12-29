#include "Sprite.h"


void Sprite::init(SDL_Renderer *ren) {

	if (ren != NULL && imagePath != "") {

		SDL_Surface* surf = SDL_LoadBMP(imagePath.c_str());
		texture = SDL_CreateTextureFromSurface(ren, surf);

		SDL_FreeSurface(surf);
	}
}

void Sprite::tick(std::list<Sprite*> otherObj) {}

Sprite::Sprite(int x, int y, int sizeX, int sizeY, std::string imagePath) :
	posX(x),
	posY(y),
	sizeX(sizeX),
	sizeY(sizeY),
	imagePath(imagePath) {}

Sprite::~Sprite() {
	if (texture != NULL)
		SDL_DestroyTexture(texture);
}
