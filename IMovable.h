#ifndef IMOVABLE_H
#define IMOVABLE_H
#include <queue>

class IMovable {
public:
	enum DIRECTION {
		UP,
		DOWN,
		LEFT,
		RIGHT
	};
	~IMovable();

	int getSpeed() { return speed; };
	int setSpeed(int newSpeed) { speed = newSpeed; };
	void addMovement(DIRECTION dir);

protected:
	int speed;
	std::queue<DIRECTION> moveBuffer;
	IMovable(int speed);

};

#endif