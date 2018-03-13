#include "AttatchedPosition.h"


int AttatchedPosition::getPositionXAsInt() const {
	float x = otherPosition.getPositionX();
	x += PositionX;
	return (int) x;
}

int AttatchedPosition::getPositionYAsInt() const {
	float y = otherPosition.getPositionY();
	y += PositionY;
	return (int) y;
}

float AttatchedPosition::getPositionX() const {
	float x = otherPosition.getPositionX();
	x += PositionX;
	return x;
}

float AttatchedPosition::getPositionY() const {
	float y = otherPosition.getPositionY();
	y += PositionY;
	return y;
}

AttatchedPosition::AttatchedPosition(int x, int y, Position &otherPos) :
	Position(x, y),
	otherPosition(otherPos)
{}


AttatchedPosition::~AttatchedPosition() {}
