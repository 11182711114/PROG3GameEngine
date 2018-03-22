#ifndef PLAYER_H
#define PLAYER_H
#include "StaticSprite.h"
#include <list>
#include "SpeedLimiter.h"
#include "AnimatedSprite.h"
#include "Level.h"

class Player : public AnimatedSprite {
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
	Level* cLevel;
public:
	Player(int x, int y, int boundX, int boundY, int sizeX, int sizeY, int speed, int& timeDiff, std::list<AnimationNode*> animation, Level* cLevel);
	~Player();
	void move(DIRECTION dir, int speed);
	void tick(std::vector<StaticSprite*> otherObj);
	void speedConstrainedMove(const Uint8* kbState);
	void setLevel(Level* level);

	void fire(const Uint8* kbState);
};

#endif
