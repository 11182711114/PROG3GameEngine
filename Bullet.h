#ifndef BULLET_H
#define BULLET_H
#include "StaticSprite.h"
#include <string>

class Bullet : public StaticSprite {
private:

	int& timeDiff;
	int speed = 1000;

public:

	void tick(std::vector<StaticSprite*> otherObjs);

	Bullet(int x, int y, int boundX, int boundY, int sizeX, int sizeY, std::string imagePath, int& timeDiff);
	~Bullet();
};

#endif