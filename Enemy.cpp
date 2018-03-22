#include "Enemy.h"
#include <stdlib.h>

Enemy::Enemy(int x, int y, int boundX, int boundY, int sizeX, int sizeY, int speed, int & timeDiff, Level * cLevel, std::string textureFile) :
	StaticSprite(x, y, boundX, boundY, sizeX, sizeY, textureFile),
	sLimit(*new SpeedLimiter(speed)),
	timeDiff(timeDiff),
	cLevel(cLevel) {}

Enemy::~Enemy() {}


void Enemy::tick(std::vector<StaticSprite*> otherObj) {
	sLimit.clear();
	speedConstrainedMove();
	if (hp <= 0)
		markDelete();
}

void Enemy::speedConstrainedMove() {
	if (!(SDL_GetTicks() - lastDirectionChange >= directionCooldown)) { // this isnt working?
		x = DIRECTION::LEFT;
		y = DIRECTION::UP;

		if (rand() % 2 == 0)
			x = DIRECTION::RIGHT;

		if (rand() % 2 == 0)
			y = DIRECTION::DOWN;

	}

	int speedX = 0;
	int speedY = 0;

	sLimit.getSpeed(speedX); sLimit.getSpeed(speedY);
	move(x, speedX);
	move(y, speedY);
	lastDirectionChange = SDL_GetTicks();
}

void Enemy::move(DIRECTION dir, int speed) {
	Position& pos = StaticSprite::pos;
	float x = pos.getPositionX();
	float y = pos.getPositionY();
	float timeDiffInSeconds = timeDiff / 1000.f;

	float newY = 0;
	float newX = 0;

	switch (dir) {
	case UP:
		newY = y - (speed * timeDiffInSeconds);
		if (!(newY<0 || newY>pos.getBoundY()))
			pos.setPositionY(newY);
		break;
	case DOWN:
		newY = y + (speed * timeDiffInSeconds);
		if (!(newY<0 || newY>pos.getBoundY()))
			pos.setPositionY(newY);
		break;
	case LEFT:
		newX = x - (speed * timeDiffInSeconds);
		if (!(newX<0 || newX>pos.getBoundY()))
			pos.setPositionX(newX);
		break;
	case RIGHT:
		newX = x + (speed * timeDiffInSeconds);
		if (!(newX<0 || newX>pos.getBoundY()))
			pos.setPositionX(newX);
		break;

	}

}

void Enemy::setLevel(Level * level) {
	cLevel = level;
}

void Enemy::decrementHP(int value) {
	hp -= value;
}

void Enemy::fire(const Uint8 * kbState) {

}
