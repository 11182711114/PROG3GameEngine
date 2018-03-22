#ifndef BACKGROUND_H
#define BACKGROUND_H
#include "StaticSprite.h"
#include <string>
#include <list>

class Background: public StaticSprite
{
private:
public:
	~Background();
	Background(int x, int y, int sizeX, int sizeY, std::string path);

	// For now --> do nothing
	void tick(std::list<StaticSprite*> otherObjs) {};
private:
	Background();
	Background(const Background& other) = delete;
	const Background& operator=(const Background& other) = delete;
};

#endif