#ifndef PLAYER_H
#define PLAYER_H
#include "StaticSprite.h"
#include <list>
#include "SpeedLimiter.h"

class Player : public StaticSprite {
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
	int hp = 50;
public:
	Player(int x, int y, int sizeX, int sizeY, int speed, int& timeDiff, std::string path);
	~Player();
	void move(DIRECTION dir, int speed);
	void tick(std::vector<StaticSprite*> otherObj);
	void speedConstrainedMove(const Uint8* kbState);
};

#endif
