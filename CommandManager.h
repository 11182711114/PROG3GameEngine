#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H
#include <SDL.h>
#include <map>
#include <list>
#include "Action.h"
#include "TextInput.h"

class CommandManager {
public:
	CommandManager(TTF_Font *font, int x, int y, int w, int h);
	CommandManager(TextInput *tIn);

	~CommandManager();
	void tick(bool paused);
	void bindKey(SDL_Scancode scancode, KeyAction& action);
	void bindEvent(SDL_EventType type, Action& action);

	void bindSystemKey(SDL_Scancode scancode, KeyAction& action);
	void bindSystemEvent(SDL_EventType type, Action& action);

	void unbindKey(SDL_Scancode scancode);
	void unbindEvent(SDL_EventType event);
private:
	int kbStateNumKeys;
	const Uint8* kbState;
	TextInput* textInput;

	std::map<SDL_Scancode, std::list<KeyAction*>*> mappedKeys;
	std::map<Uint32, std::list<Action*>*> mappedEvents;

	std::map<SDL_Scancode, std::list<KeyAction*>*> mappedSystemKeys;
	std::map<Uint32, std::list<Action*>*> mappedSystemEvents;

	void checkKbState();
	void checkSystemKbState();
	void pollEvents();
};

#endif