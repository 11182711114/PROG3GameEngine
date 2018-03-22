#include "AnimatedSprite.h"
#include <iostream>



AnimatedSprite::AnimatedSprite(int x, int y, int boundX, int boundY, int sizeX, int sizeY, std::list<AnimationNode*> animation) :
	StaticSprite(x, y, boundX, boundY, sizeX, sizeY, ""),
	animation(animation)
{}

AnimatedSprite::~AnimatedSprite() {}

void AnimatedSprite::animate() {
	AnimationNode* current = animation.front();

	if (current->type == AnimationNode::NodeType::DELAY) {
		AnimationNode* back = animation.back();
		current->delayTicks--;		

		if (current->delayTicks <= 0) {
			current->delayTicks = current->defaultDelay;
			animation.pop_front();
			animation.push_back(current);
		}
	}
	else {
		StaticSprite::setSurface(current->surface);
		StaticSprite::setTexture(current->texture);
		animation.pop_front();
		animation.push_back(current);
	}
}
void AnimatedSprite::init(SDL_Renderer * ren) {
	initialized = true;
	if (ren != NULL) {

		for (AnimationNode* node : animation) {
			if (node->type == AnimationNode::NodeType::TEXTURE) {
				SDL_Surface* surf = SDL_LoadBMP(node->imagePath.c_str());
				if (surf == NULL)
					std::cout << "something wrong initializing surface in AnimatedSprite" << std::endl;
				node->surface = surf;
				node->texture = SDL_CreateTextureFromSurface(ren, surf);
				if (node->texture == NULL)
					std::cout << "something wrong initializing texture in AnimatedSprite" << std::endl;
			}
		}

	}
}
void AnimatedSprite::tick(std::vector<StaticSprite*> otherObj) {
	animate();
}
