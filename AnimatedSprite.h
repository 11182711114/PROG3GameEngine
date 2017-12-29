#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "Sprite.h"
#include <queue>
#include <string>

struct AnimationNode {
	enum NodeType {
		TEXTURE,
		DELAY
	};
	std::string imagePath;
	SDL_Texture* texture;
	NodeType type;
	int delayTicks;

	// Texture node const
	AnimationNode(std::string imagePath):
		imagePath(imagePath), 
		type(NodeType::TEXTURE),
		delayTicks(0),
		texture(nullptr) {}

	// Delay node const
	AnimationNode(int delayTicks) :
		delayTicks(delayTicks),
		type(NodeType::DELAY),
		texture(nullptr) {}
};


class AnimatedSprite : public Sprite {
public:
	AnimatedSprite(int x, int y, int sizeX, int sizeY, std::list<AnimationNode*> animation);
	~AnimatedSprite();
	void animate();
	void init(SDL_Renderer* ren);
	void tick(std::list<Sprite*> otherObj);
private:
	std::list<AnimationNode*> animation;

};

#endif
