#include "Player.h"
#include <iostream>
#include "SpeedLimiter.h"

Player::Player(int x, int y, int sizeX, int sizeY, int speed,int& timeDiff, std::string path) : 
	StaticSprite(x, y, sizeX, sizeY, path),
	sLimit(*new SpeedLimiter(speed)),
	timeDiff(timeDiff)
{}

Player::~Player() {}

void Player::tick(std::vector<StaticSprite*> otherObj) {
	StaticSprite::tick(otherObj);
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

void Player::move(DIRECTION dir, int speed) {
	Position& pos = StaticSprite::pos;
	float x = pos.getPositionX();
	float y = pos.getPositionY();
	float timeDiffInSeconds = timeDiff / 1000.f;
	
	switch (dir) {
	case UP:
		pos.setPositionY(y - (speed * timeDiffInSeconds));
		break;
	case DOWN:
		pos.setPositionY(y + (speed * timeDiffInSeconds));
		break;
	case LEFT:
		pos.setPositionX(x - (speed * timeDiffInSeconds));
		break;
	case RIGHT:
		pos.setPositionX(x + (speed * timeDiffInSeconds));
		break;

	}
}
