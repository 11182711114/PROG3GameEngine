#include "Animation.h"

template<typename T>
Animation::Animation(T * object, void(T::* mf)(SDL_Event &)):
	Action(object, mf)
{
}


Animation::~Animation()
{
}

void Animation::execute() {
	delete sprite.getTexture();


}
