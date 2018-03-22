#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "StaticSprite.h"
#include <queue>
#include <string>

struct AnimationNode {
	enum NodeType {
		TEXTURE,
		DELAY
	};
	std::string imagePath;
	SDL_Texture* texture;
	SDL_Surface* surface;
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

	~AnimationNode() {
		SDL_DestroyTexture(texture);
		SDL_FreeSurface(surface);
	}
};


class AnimatedSprite : public StaticSprite {
public:
	AnimatedSprite(int x, int y, int sizeX, int sizeY, std::list<AnimationNode*> animation);
	~AnimatedSprite();
	void animate();
	void init(SDL_Renderer* ren);
	void tick(std::vector<StaticSprite*> otherObj);
private:
	std::list<AnimationNode*> animation;

};

#endif
