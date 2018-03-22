#include "Player.h"
#include <iostream>
#include "SpeedLimiter.h"
#include "Level.h"
#include "Bullet.h"

Player::Player(int x, int y, int boundX, int boundY, int sizeX, int sizeY, int speed,int& timeDiff, std::list<AnimationNode*> animation, Level* cLevel) :
	AnimatedSprite(x, y, boundX, boundY, sizeX, sizeY, animation),
	sLimit(*new SpeedLimiter(speed)),
	timeDiff(timeDiff),
	cLevel(cLevel)
{}

Player::~Player() {}

void Player::tick(std::vector<StaticSprite*> otherObj) {
	AnimatedSprite::tick(otherObj);
	sLimit.clear();
}

// Does not work properly because as is, 
// each key generates a call to this function 
// which means speed in either direction will double if both the other directional keys are pressed
// e.g. right speed will double if up and down are pressed
void Player::speedConstrainedMove(const Uint8* kbState) {
	int speedX = 0;
	int speedY = 0;
	DIRECTION	x = DIRECTION::LEFT;
	DIRECTION	y = DIRECTION::UP;

	if (kbState[SDL_SCANCODE_LEFT] && !kbState[SDL_SCANCODE_RIGHT]) {
		sLimit.getSpeed(speedX);
		x = DIRECTION::LEFT;
	}
	else if (kbState[SDL_SCANCODE_RIGHT] && !kbState[SDL_SCANCODE_LEFT]) {
		sLimit.getSpeed(speedX);
		x = DIRECTION::RIGHT;
	}
	
	if (kbState[SDL_SCANCODE_UP] && !kbState[SDL_SCANCODE_DOWN]) {
		sLimit.getSpeed(speedY);
		y = DIRECTION::UP;
	}
	else if (kbState[SDL_SCANCODE_DOWN] && !kbState[SDL_SCANCODE_UP]) {
		sLimit.getSpeed(speedY);
		y = DIRECTION::DOWN;
	}

	//std::cout << "speed x:" << speedX << " speed y: " << speedY << std::endl;

	move(x, speedX);
	move(y, speedY);
}

void Player::setLevel(Level * level) {
	cLevel = level;
}

void Player::fire(const Uint8 * kbState) {
	// int x, int y, int sizeX, int sizeY, std::string imagePath, int& timeDiff
	Bullet *bullet = new Bullet(pos.getPositionXAsInt(), pos.getPositionYAsInt()+sizeY/2, pos.getBoundX(), pos.getBoundY(), 20, 7, "C:/Users/Fredrik/source/repos/cBH/media/rocketR.bmp", timeDiff);
	cLevel->addSprite(bullet);
}

void Player::move(DIRECTION dir, int speed) {
	Position& pos = StaticSprite::pos;
	float x = pos.getPositionX();
	float y = pos.getPositionY();
	float timeDiffInSeconds = timeDiff / 1000.f;
	
	float newY = 0;
	float newX = 0;

	switch (dir) {
	case UP:
		newY = y - (speed * timeDiffInSeconds);
		if (! (newY<0 || newY>pos.getBoundY()))
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
