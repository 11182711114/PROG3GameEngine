#ifndef SPRITE_H
#define SPRITE_H
#include <SDL.h>
#include <string>
#include <list>
#include "Position.h"
#include <vector>

class StaticSprite {
private:
	SDL_Texture * texture;
	SDL_Surface *surface;
	bool deletionMark;

public:
	virtual ~StaticSprite();
		
	virtual void init(SDL_Renderer* ren);

	virtual void tick(std::vector<StaticSprite*> otherObj);

	// Getters setter
	int getSizeX() const { return sizeX; };
	int getSizeY() const { return sizeY; };
	Position* getPosition() { return &pos; };
	std::string getPath() const { return imagePath; };
	SDL_Texture* getTexture() const { return texture; };
	virtual void render(SDL_Renderer *renderer);

	bool toBeDeletedStatus() { return deletionMark; }
	void markDelete() {	deletionMark = true; }

	StaticSprite(Position pos, int sizeX, int sizeY, std::string imagePath);
	StaticSprite(int x, int y, int sizeX, int sizeY, std::string imagePath);
	StaticSprite(int x, int y, int sizeX, int sizeY, SDL_Texture *texture);

protected:
	std::string imagePath;
	Position pos;
	int sizeX;
	int sizeY;

	void setTexture(SDL_Texture*  texture) { this->texture = texture; };
	void setSurface(SDL_Surface* surface) { this->surface = surface; }

	std::vector<StaticSprite*> collisionDetection(std::vector<StaticSprite*> otherObj);
private:
	// This is a base class that should not be instanciated by itself.
	StaticSprite(const StaticSprite& other) = delete;
	const StaticSprite& operator=(const StaticSprite& other) = delete;

	bool intersect(StaticSprite* other); 
	SDL_Rect makeRect();

	bool isPixelTransperant(Uint32 pixel, SDL_PixelFormat *format);
	bool pixelIntersect(int x, int y);
	bool fastIntersect(StaticSprite *other);

};

#endif
