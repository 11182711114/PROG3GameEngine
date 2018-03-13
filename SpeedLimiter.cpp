#include "SpeedLimiter.h"
#include <list>


SpeedLimiter::SpeedLimiter(int maxSpeed):
	maxSpeed(maxSpeed)
{}


SpeedLimiter::~SpeedLimiter() {}

void SpeedLimiter::getSpeed(int &ref) {
	refs.push_back(&ref);
	int maxSpeedPerRef = maxSpeed / refs.size();
	for (int *ref : refs) {
		*ref = maxSpeedPerRef;
	}
}

void SpeedLimiter::clear() {
	refs = {};
}
