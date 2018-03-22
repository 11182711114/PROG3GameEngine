#include "AnimatedSprite.h"
#include <iostream>



AnimatedSprite::AnimatedSprite(int x, int y, int sizeX, int sizeY, std::list<AnimationNode*> animation) :
	StaticSprite(x, y, sizeX, sizeY, ""),
	animation(animation)
{}

AnimatedSprite::~AnimatedSprite() {}

void AnimatedSprite::animate() {

	// This is retarded
	AnimationNode* current = animation.front();

	if (current->type == AnimationNode::NodeType::DELAY) {
		AnimationNode* back = animation.back();
		current->delayTicks--;
		if (current->delayTicks <= 0)
			animation.pop_front();

		if (back->type == AnimationNode::NodeType::DELAY) {
			back->delayTicks++;
		} 
		else {
			AnimationNode* newDelay = new AnimationNode(1);
			animation.push_back(newDelay);
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
