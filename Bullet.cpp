#include "Bullet.h"
#include <iostream>
#include "Enemy.h"

void Bullet::tick(std::vector<StaticSprite*> otherObjs) {


	Position& pos = StaticSprite::pos;
	float x = pos.getPositionX();
	float y = pos.getPositionY();
	float timeDiffInSeconds = timeDiff / 1000.f;


	pos.setPositionX(x + (speed * timeDiffInSeconds));

	if (pos.outOfBounds())
		markDelete();
	
	for (auto v : collisionDetection(otherObjs)) {
 		Enemy* en = dynamic_cast<Enemy*>(v);
		if (en != nullptr) {
 			en->decrementHP(10);
			this->markDelete();
		}
	}

}

Bullet::Bullet(int x, int y, int boundX, int boundY, int sizeX, int sizeY, std::string imagePath, int& timeDiff):
	StaticSprite(x, y, boundX, boundY, sizeX, sizeY, imagePath),
	timeDiff(timeDiff)
{}

Bullet::~Bullet() {
	std::cout << "deleted bullet" << std::endl;
}
