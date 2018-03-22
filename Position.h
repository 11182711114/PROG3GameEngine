#ifndef POSITION_H
#define POSITION_H
class Position {
protected:
	float PositionX;
	float PositionY;

	int boundX;
	int boundY;

public:
	int getPositionXAsInt() { return static_cast<int>(PositionX); };
	int getPositionYAsInt() { return static_cast<int>(PositionY); };
	float getPositionX() { return PositionX; };
	float getPositionY() { return PositionY; };
	void setPositionX(float x) { PositionX = x; };
	void setPositionY(float y) { PositionY = y; };
	int getBoundX();
	int getBoundY();

	virtual bool outOfBounds();

	Position(int x, int y, int boundX, int boundY);
	~Position();

};

#endif