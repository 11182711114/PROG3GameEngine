#pragma once
#include "Position.h"

class AttatchedPosition : public Position {
private:
	Position &otherPosition;
public:
	virtual int getPositionXAsInt() const;
	virtual int getPositionYAsInt() const;
	virtual float getPositionX() const;
	virtual float getPositionY() const;

	// Not allowed to reposition to avoid it getting treated as an absolute position, should probably not inherit from Position and just be handled sepparatly.
	virtual void setPositionX(float x) {};
	virtual void setPositionY(float y) {};

	AttatchedPosition(int x, int y, Position &otherPos);
	~AttatchedPosition();
};

