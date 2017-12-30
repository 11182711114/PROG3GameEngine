#include "Player.h"
#include <iostream>

Player::Player(int x, int y, int sizeX, int sizeY, int speed,int& timeDiff, std::string path) : 
	Sprite(x, y, sizeX, sizeY, path),
	IMovable(speed),
	timeDiff(timeDiff)
{}

Player::~Player() {}

void Player::tick(std::list<Sprite*> otherObj) {
	int size = moveBuffer.size();
	if (moveBuffer.size() == 0)
		return;

	IMovable::DIRECTION dir = IMovable::moveBuffer.front();
	while(moveBuffer.size() > 0) {
		move(timeDiff, dir);

		IMovable::moveBuffer.pop();
	}
}

void Player::moveWithState(const Uint8* kbState) {
	if (kbState[SDL_SCANCODE_LEFT])
		IMovable::moveBuffer.push(IMovable::DIRECTION::LEFT);
	if (kbState[SDL_SCANCODE_RIGHT])
		IMovable::moveBuffer.push(IMovable::DIRECTION::RIGHT);
	if (kbState[SDL_SCANCODE_UP])
		IMovable::moveBuffer.push(IMovable::DIRECTION::UP);
	if (kbState[SDL_SCANCODE_DOWN])
		IMovable::moveBuffer.push(IMovable::DIRECTION::DOWN);
		
}

void Player::move(int timeDiff, DIRECTION dir) {
	float newX = Sprite::getPositionX();
	float newY = Sprite::getPositionY();
	float timeDiffSecs = ((float) timeDiff) / 1000.f ;
	switch (dir) {
	case UP:
		newY -= (IMovable::speed * timeDiffSecs);
		break;
	case DOWN:
		newY += (IMovable::speed * timeDiffSecs);
		break;
	case LEFT:
		newX -= (IMovable::speed * timeDiffSecs);
		break;
	case RIGHT:
		newX += (IMovable::speed * timeDiffSecs);
		break;
	}
	Sprite::setPositionX(newX);
	Sprite::setPositionY(newY);
}
