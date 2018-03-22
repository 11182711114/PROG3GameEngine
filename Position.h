#ifndef POSITION_H
#define POSITION_H
class Position {
protected:
	float PositionX;
	float PositionY;

public:
	virtual int getPositionXAsInt() { return static_cast<int>(PositionX); };
	virtual int getPositionYAsInt() { return static_cast<int>(PositionY); };
	virtual float getPositionX() { return PositionX; };
	virtual float getPositionY() { return PositionY; };
	virtual void setPositionX(float x) { PositionX = x; };
	virtual void setPositionY(float y) { PositionY = y; };
	Position(int x, int y);
	~Position();

};

#endif