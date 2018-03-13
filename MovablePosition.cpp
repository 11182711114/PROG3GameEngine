#include "MovablePosition.h"

void MovablePosition::move(int newX, int newY) {
	Position::PositionX = newX;
	Position::PositionY = newY;
}

void MovablePosition::move(int speedPerSecond, int timeDiff, MovablePosition::DIRECTION dir) {
	int newX = Position::PositionX;
	int newY = Position::PositionY;

	//	Frame independent movement
	float timeDiffInSeconds = timeDiff / 1000.f;

	switch(dir) {
	case UP:
		newY -= timeDiffInSeconds * timeDiff;
		break;
	case DOWN:
		newY += timeDiffInSeconds * timeDiff;
		break;
	case LEFT:
		newX -= timeDiffInSeconds * timeDiff;
		break;
	case RIGHT:
		newX += timeDiffInSeconds * timeDiff;
		break;
	}
	
	// Check if within bounds
	if (newX > boundX)
		newX = boundX;
	if (newX < 0)
		newX = 0;

	if (newY > boundY)
		newY = boundY;
	if (newY < 0)
		newY = 0;

	// move
	move(newX, newY);
}

MovablePosition::MovablePosition(int x, int y, int boundX, int boundY):
	Position(x,y),
	boundX(boundX),
	boundY(boundY)
{}

MovablePosition::~MovablePosition() {}
