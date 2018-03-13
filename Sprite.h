#ifndef SPRITE_H
#define SPRITE_H
#include <SDL.h>
#include <string>
#include <list>
#include "Position.h"

class Sprite {
private:
	SDL_Texture * texture;
public:
	virtual ~Sprite();
		
	virtual void init(SDL_Renderer* ren);

	virtual void tick(std::list<Sprite*> otherObj);

	// Getters setter
	int getSizeX() const { return sizeX; };
	int getSizeY() const { return sizeY; };
	Position* getPosition() { return &pos; };
	std::string getPath() const { return imagePath; };
	SDL_Texture* getTexture() const { return texture; };
	virtual void render(SDL_Renderer* renderer);
protected:
	std::string imagePath;
	Position pos;
	int sizeX;
	int sizeY;
	Sprite(Position pos, int sizeX, int sizeY, std::string imagePath);
	Sprite(int x, int y, int sizeX, int sizeY, std::string imagePath);
	void setTexture(SDL_Texture*  texture) { this->texture = texture; };
private:
	// This is a base class that should not be instanciated by itself.
	Sprite(const Sprite& other) = delete;
	const Sprite& operator=(const Sprite& other) = delete;
};

#endif
