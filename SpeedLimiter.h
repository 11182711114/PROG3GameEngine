#ifndef SPEEDLIMITER_H
#define SPEEDLIMITER_H
#include <list>

class SpeedLimiter {
public:
	SpeedLimiter(int maxSpeed);
	~SpeedLimiter();
	void getSpeed(int &ref);
	void clear();
private:
	int maxSpeed;
	std::list<int*> refs;
};

#endif