#ifndef BACKGROUND_H
#define BACKGROUND_H
#include "Sprite.h"
#include <string>
#include <list>

class Background: public Sprite
{
private:
public:
	~Background();
	Background(int x, int y, int sizeX, int sizeY, std::string path);

	// For now --> do nothing
	void tick(std::list<Sprite*> otherObjs) {};
private:
	Background();
	Background(const Background& other) = delete;
	const Background& operator=(const Background& other) = delete;
};

#endif