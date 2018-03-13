#ifndef PLAYER_H
#define PLAYER_H
#include "Sprite.h"
#include <list>
#include "SpeedLimiter.h"

class Player : public Sprite {
public:
	enum DIRECTION {
		UP,
		DOWN,
		LEFT,
		RIGHT
	};
private:
	int& timeDiff;
	SpeedLimiter sLimit;
public:
	Player(int x, int y, int sizeX, int sizeY, int speed, int& timeDiff, std::string path);
	~Player();
	void move(int timeDiff, DIRECTION dir, int speed);
	void tick(std::list<Sprite*> otherObj);
	void moveVertical(const Uint8* kbState);
};

#endif
