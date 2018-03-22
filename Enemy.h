#ifndef ENEMY_H
#define ENEMY_H
#include "StaticSprite.h"
#include "SpeedLimiter.h"
#include "Level.h"

class Enemy : public StaticSprite{
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
	int hp = 10;
	Level* cLevel;

	int lastDirectionChange = 0;
	int directionCooldown = 1000;

	DIRECTION x = DIRECTION::LEFT;
	DIRECTION y = DIRECTION::UP;
public:
	Enemy(int x, int y, int boundX, int boundY, int sizeX, int sizeY, int speed, int& timeDiff, Level* cLevel, std::string textureFile);
	~Enemy();

	void move(DIRECTION dir, int speed);
	void tick(std::vector<StaticSprite*> otherObj);
	void speedConstrainedMove();
	void setLevel(Level* level);

	void decrementHP(int value);

	void fire(const Uint8* kbState);

};

#endif