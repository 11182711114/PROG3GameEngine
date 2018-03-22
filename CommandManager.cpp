#include "CommandManager.h"
#include <SDL.h>
#include <iostream>
#include "CimpleBulletEngine.h"


CommandManager::CommandManager(TextInput *tIn) :
	textInput(tIn) {
	kbState = SDL_GetKeyboardState(&kbStateNumKeys);
}

CommandManager::CommandManager(int x, int y, int w, int h):
	textInput(new TextInput(x, y, w, h)) {
	kbState = SDL_GetKeyboardState(&kbStateNumKeys);
}


CommandManager::~CommandManager() {
	delete textInput;
}

void CommandManager::tick(bool paused) {
	if (!paused)
		checkKbState();
	checkSystemKbState();
	pollEvents();
}

void CommandManager::checkKbState() {
	for (std::map<SDL_Scancode, std::list<KeyAction*>*>::iterator it = mappedKeys.begin(); it != mappedKeys.end(); ++it) {
		SDL_Scancode scancode = it->first;
		if (kbState[scancode]) {
			std::list<KeyAction*>* keyList = it->second;

			if (keyList == NULL)
				return;
			for (KeyAction* act : *keyList)
				act->execute(kbState);
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

void CommandManager::checkSystemKbState() {
	for (std::map<SDL_Scancode, std::list<KeyAction*>*>::iterator it = mappedSystemKeys.begin(); it != mappedSystemKeys.end(); ++it) {
		SDL_Scancode scancode = it->first;
		if (kbState[scancode]) {
			std::list<KeyAction*>* keyList = it->second;

			if (keyList == NULL)
				return;
			for (KeyAction* act : *keyList)
				act->execute(kbState);
		}
	}
}

void CommandManager::bindKey(SDL_Scancode scancode, KeyAction & action) {
	std::list<KeyAction*>* keyActions = mappedKeys[scancode];
	if (keyActions == NULL) {
		keyActions = new std::list<KeyAction*>();
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

void CommandManager::bindSystemKey(SDL_Scancode scancode, KeyAction & action) {
	std::list<KeyAction*>* keyActions = mappedSystemKeys[scancode];
	if (keyActions == NULL) {
		keyActions = new std::list<KeyAction*>();
		mappedSystemKeys[scancode] = keyActions;
	}
	keyActions->push_back(&action);
}

void CommandManager::bindSystemEvent(SDL_EventType type, Action & action) {
	std::list<Action*>* eventActions = mappedSystemEvents[type];
	if (eventActions == NULL) {
		eventActions = new std::list<Action*>();
		mappedSystemEvents[type] = eventActions;
	}
	eventActions->push_back(&action);
}

void CommandManager::unbindKey(SDL_Scancode scancode) {
	std::list<KeyAction*>* keyActions = mappedKeys[scancode];
	if (keyActions == NULL) {
		keyActions = new std::list<KeyAction*>();
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

void CommandManager::acceptKeyInput(const Uint8* kbState) {
	textInput->toggleActive();
}

void CommandManager::passRenderer(SDL_Renderer * renderer) {
	textInput->setRenderer(renderer);
}
	
