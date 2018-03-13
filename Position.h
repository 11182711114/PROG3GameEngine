#pragma once
class Position {
protected:
	float PositionX;
	float PositionY;

public:
	virtual int getPositionXAsInt() { return PositionX; };
	virtual int getPositionYAsInt() { return PositionY; };
	virtual float getPositionX() { return PositionX; };
	virtual float getPositionY() { return PositionY; };
	virtual void setPositionX(float x) { PositionX = x; };
	virtual void setPositionY(float y) { PositionY = y; };
	Position(int x, int y);
	~Position();

};

