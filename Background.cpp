#include "Background.h"



Background::~Background() {}

Background::Background(int x, int y, int sizeX, int sizeY, std::string path) :
	StaticSprite(x, y, 0, 0, sizeX, sizeY, path)
{
		
}

