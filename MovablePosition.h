#pragma once
#include "Position.h"

class MovablePosition: public Position {
public:
	enum DIRECTION {
		LEFT,
		RIGHT,
		UP,
		DOWN
	};
private:
	int boundX;
	int boundY;
public:

	// Instant move, ignores bounds
	void move(int newX, int newY);
	// Frame independant movement with a max speed, considers bounds
	void move(int speedPerSecond, int timeDiff, MovablePosition::DIRECTION dir);

	MovablePosition(int x, int y, int boundX, int boundY);
	~MovablePosition();
};

