#include "IMovable.h"


IMovable::IMovable(int speed) : 
	speed(speed) 
{}


IMovable::~IMovable() {}

void IMovable::addMovement(DIRECTION dir) {
	moveBuffer.push(dir);
}

