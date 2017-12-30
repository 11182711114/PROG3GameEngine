#pragma once
#include <SDL.h>
#include <map>
#include <list>
#include "Action.h"

class CommandManager {
public:
	CommandManager();
	~CommandManager();
	void tick();
	void bindKey(SDL_Scancode scancode, KeyAction& action);
	void bindEvent(SDL_EventType type, Action& action);
	void unbindKey(SDL_Scancode scancode);
	void unbindEvent(SDL_EventType event);
private:
	int kbStateNumKeys;
	const Uint8* kbState;
	std::map<SDL_Scancode, std::list<KeyAction*>*> mappedKeys;
	std::map<Uint32, std::list<Action*>*> mappedEvents;

	void checkKbState();
	void pollEvents();
};

