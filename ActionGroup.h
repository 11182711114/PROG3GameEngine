#ifndef ACTIONGROUP_H
#define ACTIONGROUP_H
#include <list>
#include <SDL.h>
#include "Action.h"

class ActionGroup {
public:
	ActionGroup(std::list<SDL_Scancode> codes, KeyAction action);
	~ActionGroup();

private:
	std::list<SDL_Scancode> scanCodes;
	KeyAction &action;

public:
	std::list<SDL_Scancode> getScancodes() const { return scanCodes; };

	void execute(const Uint8* state) { action.execute(state); };
	

};

#endif