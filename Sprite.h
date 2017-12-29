#ifndef SPRITE_H
#define SPRITE_H
#include <SDL.h>
#include <string>
#include <list>

class Sprite
{
private:
	SDL_Texture * texture;
public:
	virtual ~Sprite();
		
	virtual void init(SDL_Renderer* ren);

	virtual void tick(std::list<Sprite*> otherObj);

	// Getters setter
	float getPositionX() { return posX; };
	float getPositionY() { return posY; };
	int getSizeX() { return sizeX; };
	int getSizeY() { return sizeY; };
	void setPositionX(float x) { posX = x; };
	void setPositionY(float y) { posY = y; };
	std::string getPath() { return imagePath; };
	SDL_Texture* getTexture() { return texture; };
protected:
	std::string imagePath;
	float posX;
	float posY;
	int sizeX;
	int sizeY;
	Sprite(int x, int y, int sizeX, int sizeY, std::string imagePath);
	void setTexture(SDL_Texture*  texture) { this->texture = texture; };
private:
	// This is a base class that should not be instanciated by itself.
	Sprite(const Sprite& other) = delete;
	const Sprite& operator=(const Sprite& other) = delete;
};

#endif
