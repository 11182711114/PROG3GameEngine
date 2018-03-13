#ifndef CIMPLEBULLETENGINE_H
#define CIMPLEBULLETENGINE_H
#include <SDL.h> 
#include <iostream> 
#include <string>
#include <list>
#include <map>
#include "Sprite.h"
#include "Action.h"
#include "CommandManager.h"

class CimpleBulletEngine {
private:
	// Constants, used for building the window or for base functionality
	const int SCREEN_WIDTH;
	const int SCREEN_HEIGHT;
	const int refreshRate;
	const std::string windowTitle;

	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	int timeDiff;
	bool quit;

	// Gameworld stuffs
	std::list<Sprite*> objects;

	// Command-action mapping
	//std::map<SDL_EventType, Action*> events;
	CommandManager cmdMgr;
public:
	CimpleBulletEngine();
	CimpleBulletEngine(int x, int y, int rr, std::string title);
	CimpleBulletEngine(const CimpleBulletEngine& other);
	~CimpleBulletEngine();
	int& getTimeDiff() { return timeDiff; };
	int start();
	void addSprite(Sprite* sprite);
	CommandManager& getCommandManager() { return cmdMgr; };
	void onQuitEvent(SDL_Event& event);
private:
	void input();
	void close();
	void renderObjects();
	void tickObjects();
};

#endif
