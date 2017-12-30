#include "CommandManager.h"
#include <SDL.h>
#include <iostream>


CommandManager::CommandManager() {
	kbState = SDL_GetKeyboardState(&kbStateNumKeys);
}


CommandManager::~CommandManager() {}

void CommandManager::tick() {
	checkKbState();
	pollEvents();
}

void CommandManager::checkKbState() {
	for (std::map<SDL_Scancode, std::list<Action*>*>::iterator it = mappedKeys.begin(); it != mappedKeys.end(); ++it) {
		SDL_Scancode scancode = it->first;
		if (kbState[scancode]) {
			std::list<Action*>* keyList = it->second;

			if (keyList == NULL)
				return;
			for (Action* act : *keyList)
				act->execute(*new SDL_Event());
		}
	}
}

void CommandManager::pollEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		std::list<Action*>* eventsList = mappedEvents[event.type];

		if (eventsList == NULL)
			return;

		for (Action* act : *eventsList) {
			if (act != NULL) {
				act->execute(event);
			}
		}
	}
}

void CommandManager::bindKey(SDL_Scancode scancode, Action & action) {
	std::list<Action*>* keyActions = mappedKeys[scancode];
	if (keyActions == NULL) {
		keyActions = new std::list<Action*>();
		mappedKeys[scancode] = keyActions;
	}
	keyActions->push_back(&action);
}

void CommandManager::bindEvent(SDL_EventType type, Action & action) {
	std::list<Action*>* eventActions = mappedEvents[type];
	if (eventActions == NULL) {
		eventActions = new std::list<Action*>();
		mappedEvents[type] = eventActions;
}
	eventActions->push_back(&action);
}

void CommandManager::unbindKey(SDL_Scancode scancode) {
	std::list<Action*>* keyActions = mappedKeys[scancode];
	if (keyActions == NULL) {
		keyActions = new std::list<Action*>();
		mappedKeys[scancode] = keyActions;
}
	*keyActions = {};
}

void CommandManager::unbindEvent(SDL_EventType event) {
	std::list<Action*>* eventActions = mappedEvents[event];
	if (eventActions == NULL) {
		eventActions = new std::list<Action*>();
		mappedEvents[event] = eventActions;
}
	*eventActions = {};
}
	
