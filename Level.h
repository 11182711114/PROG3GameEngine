#ifndef LEVEL_H
#define LEVEL_H
#include <list>
#include "Sprite.h"
#include "Physic.h"


class Level {
private:
	std::list<Sprite*> sprites;
	std::list<Physic*> physics;
public:
	void addSprite(Sprite &sprite);

	Level();
	~Level();
};

#endif