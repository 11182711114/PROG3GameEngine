#include "DynamicTextureSprite.h"



DynamicTextureSprite::DynamicTextureSprite(Position pos, int sizeX, int sizeY, std::string imagePath, SDL_Texture *textures, int nrTextures) :
	StaticSprite(pos, sizeX, sizeY, imagePath),
	textures(textures),
	nrTextures(nrTextures)
{
}


DynamicTextureSprite::DynamicTextureSprite(int x, int y, int sizeX, int sizeY, std::string imagePath, SDL_Texture *textures, int nrTextures) :
	StaticSprite(x, y, sizeX, sizeY, imagePath),
	textures(textures),
	nrTextures(nrTextures) {
}



DynamicTextureSprite::~DynamicTextureSprite() {}

void DynamicTextureSprite::switchTexture(int textureIndex) {
	if (textureIndex > nrTextures || textureIndex < 0)
		return;
	

}
