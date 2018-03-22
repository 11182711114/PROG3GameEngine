#include "StaticSprite.h"
#include <iostream>
#include "Position.h"

void StaticSprite::init(SDL_Renderer *ren) {

	if (ren != NULL && imagePath != "") {

		SDL_Surface* surf = SDL_LoadBMP(imagePath.c_str());
		texture = SDL_CreateTextureFromSurface(ren, surf);

		this->surface = surf;
		this->initialized = true;
	}
}

void StaticSprite::tick(std::vector<StaticSprite*> otherObj) {
	collisionDetection(otherObj);
}

void StaticSprite::render(SDL_Renderer *renderer) {
	SDL_Rect rect = makeRect(); 
	
	/*SDL_SetRenderDrawColor(renderer,
		0xFF,
		0,
		0,
		0xFF);

	SDL_RenderDrawRect(renderer, &rect);*/

	//std::cout << "rendering: " << spr->getPath() << " @ x: " << spr->getPositionX() << " y: " << spr->getPositionY() << " sizeX: " << spr->getSizeX() << " sizeY: " << spr->getSizeY() << std::endl;
	if (!initialized)
		init(renderer);
	if (texture != NULL) {
		if (SDL_RenderCopy(renderer, texture, NULL, &rect) != 0)
			std::cout << "error: " << SDL_GetError() << std::endl;
	}
}

StaticSprite::StaticSprite(Position pos, int sizeX, int sizeY, std::string imagePath) :
	pos(pos),
	sizeX(sizeX),
	sizeY(sizeY),
	imagePath(imagePath) 
{}

StaticSprite::StaticSprite(int x, int y, int boundX, int boundY, int sizeX, int sizeY, std::string imagePath) :
	pos(*new Position(x, y, boundX, boundY)),
	sizeX(sizeX),
	sizeY(sizeY),
	imagePath(imagePath) 
{}

StaticSprite::StaticSprite(int x, int y, int boundX, int boundY, int sizeX, int sizeY, SDL_Texture *texture) :
	pos(*new Position(x, y, 0, 0)),
	sizeX(sizeX),
	sizeY(sizeY),
	texture(texture) {}

std::vector<StaticSprite*> StaticSprite::collisionDetection(std::vector<StaticSprite*> otherObj) {
	std::vector<StaticSprite*> collisions;

	// This is inefficient
	for (StaticSprite* spr : otherObj) {
		if (spr != this) {
			if (intersect(spr))
				collisions.push_back(spr);
		}
	}


	return collisions;
}

bool StaticSprite::intersect(StaticSprite * other) {
	/*SDL_Rect thisRect = this->makeRect();
	SDL_Rect otherRect = other->makeRect();
	SDL_Rect res = {};*/

	if (fastIntersect(other)) {
		//std::cout << "Fast intersect detected" << std::endl;
		return true;

		//if (this->surface == NULL) {
		//	std::cout << "surface is null" << std::endl;
		//	return false;
		//}

		//SDL_LockSurface(this->surface);

		//SDL_Surface* thisSurf = this->surface;

		//Uint32 pixel;
		//int bpp = thisSurf->format->BytesPerPixel;

		//for (int x = 0; x < this->sizeX; x++) {
		//	for (int y = 0; y < this->sizeY; y++) {
		//		char* p = (char*)thisSurf->pixels + y * thisSurf->pitch + x * bpp; 
		//		int pixelPosX = this->getPosition()->getPositionXAsInt()+x;
		//		int pixelPosY = this->getPosition()->getPositionYAsInt()+y;


		//		switch (bpp) {
		//		case 1:
		//			pixel = *p; break;
		//		case 2:
		//			pixel = *(Uint16*)p; break;
		//		case 3:
		//			if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
		//				pixel = p[0] << 16 | p[1] << 8 | p[2];
		//			else
		//				pixel = p[0] | p[1] << 8 | p[2] << 16;
		//			break;
		//		case 4:
		//			pixel = *(Uint32*)p; break;
		//		}

		//		if (false){//other->pixelIntersect(pixelPosX, pixelPosY)) {
		//			std::cout << "Pixel intersect detected" << std::endl;
		//			return true;

		//		}

		//	}

		//}

		//SDL_UnlockSurface(this->surface);

	}


	return false;
}

// Doesnt work properly
bool StaticSprite::pixelIntersect(int x, int y) {
	SDL_LockSurface(this->surface);
	SDL_Surface* thisSurf = this->surface;

	Uint32 pixel;
	int bpp = thisSurf->format->BytesPerPixel; 
	
	/*
		Have to find the relative position in the surface of this to the absolute position X in space
	
	*/
	int relativeX = x - this->getPosition()->getPositionXAsInt();
	int relativeY = y - this->getPosition()->getPositionYAsInt();

	if (!(relativeX >= 0 && relativeY >= 0 && relativeX <= sizeX && relativeY <= sizeY)) {
		SDL_UnlockSurface(thisSurf);
		return false;
	}

	char* p = (char*)thisSurf->pixels + relativeX * thisSurf->pitch + relativeY * bpp;

	switch (bpp) {
	case 1:
		pixel = *p; break;
	case 2:
		pixel = *(Uint16*)p; break;
	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			pixel = p[0] << 16 | p[1] << 8 | p[2];
		else
			pixel = p[0] | p[1] << 8 | p[2] << 16;
		break;
	case 4:
		pixel = *(Uint32*)p; break;
	}
	SDL_UnlockSurface(this->surface);
	
	return !isPixelTransperant(pixel, thisSurf->format);
}

bool StaticSprite::fastIntersect(StaticSprite * other) {
	SDL_Rect thisR = makeRect();
	SDL_Rect otherR = other->makeRect();

	return !(
		thisR.x		+ thisR.w	< otherR.x	|| 
		otherR.x	+ otherR.w	< thisR.x	|| 
		thisR.y		+ thisR.h	< otherR.y	|| 
		otherR.y	+ otherR.h	< thisR.y
		);
		
}

SDL_Rect StaticSprite::makeRect() {
	return { pos.getPositionXAsInt(), pos.getPositionYAsInt(), sizeX, sizeY };
}

bool StaticSprite::isPixelTransperant(Uint32 pixel, SDL_PixelFormat * format) {
	Uint8 red, green, blue, alpha;
	SDL_GetRGBA(pixel, format, &red, &green, &blue, &alpha);
	return alpha == 0;
}

StaticSprite::~StaticSprite() {
	if (texture != NULL)
		SDL_DestroyTexture(texture);
	if (surface != NULL)
		SDL_FreeSurface(surface);
}