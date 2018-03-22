#pragma once
#include "StaticSprite.h"
#include "Action.h"

class Animation: public Action {
public:
	template <typename T>
	Animation(T *object, void(T::*mf)(SDL_Event&));
	~Animation();


	void execute();

private:
	StaticSprite &sprite;
	
	SDL_Texture *texture;





};
