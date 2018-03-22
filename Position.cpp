#include "Position.h"



int Position::getBoundX() {
	return boundX; 
}

int Position::getBoundY() {
	return boundY;
}

bool Position::outOfBounds() {
	return PositionX>boundX || PositionY>boundY || PositionX<=0 || PositionY<=0;
}

Position::Position(int x, int y, int boundX, int boundY):
	PositionX(x), 
	PositionY(y),
	boundX(boundX),
	boundY(boundY)
{}


Position::~Position() {}
