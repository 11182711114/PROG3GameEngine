#ifndef DYNAMICTEXTURESPRITE_H
#define DYNAMICTEXTURESPRITE_H

#include "StaticSprite.h"
#include <vector>

class DynamicTextureSprite: public StaticSprite
{
private:
	SDL_Texture *textures;
	int nrTextures;

public:
	DynamicTextureSprite(Position pos, int sizeX, int sizeY, std::string imagePath, SDL_Texture *inTextures, int nrTextures);
	DynamicTextureSprite(int x, int y, int sizeX, int sizeY, std::string imagePath, SDL_Texture *textures, int nrTextures);
	~DynamicTextureSprite();


	void switchTexture(int textureIndex);



};

#endif