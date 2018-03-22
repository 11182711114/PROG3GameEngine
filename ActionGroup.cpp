#include "ActionGroup.h"

ActionGroup::ActionGroup(std::list<SDL_Scancode> codes, KeyAction action) :
	scanCodes(codes),
	action(action)
{
}

ActionGroup::~ActionGroup()
{
}
