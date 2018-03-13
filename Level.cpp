#include "Level.h"



void Level::addSprite(Sprite &sprite) {
	sprites.push_back(&sprite);
}

Level::Level() {}


Level::~Level() {}
