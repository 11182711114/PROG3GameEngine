#ifndef PLAYER_H
#define PLAYER_H
#include "Sprite.h"
#include "IMovable.h"
#include <list>

class Player : public Sprite, public IMovable {
	int& timeDiff;
public:
	Player(int x, int y, int sizeX, int sizeY, int speed, int& timeDiff, std::string path);
	~Player();
	void move(int timeDiff, IMovable::DIRECTION dir);
	void tick(std::list<Sprite*> otherObj);
	void onEvent(SDL_Event& event);
};

#endif
