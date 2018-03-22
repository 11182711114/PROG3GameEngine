#ifndef CIMPLEBULLETENGINE_H
#define CIMPLEBULLETENGINE_H
#include <SDL.h> 
#include <iostream> 
#include <string>
#include <list>
#include <map>
#include "StaticSprite.h"
#include "Action.h"
#include "CommandManager.h"
#include "Background.h"
#include "Level.h"
#include <vector>
#include <SDL_ttf.h>

// This entire project violates KISS so badly it should get life in prison
class CimpleBulletEngine {
private:
	// Constants, used for building the window or for base functionality
	const int SCREEN_WIDTH;
	const int SCREEN_HEIGHT;
	const int refreshRate;
	const std::string windowTitle;

	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	TTF_Font *font;

	int timeDiff;
	bool quit;
	bool paused;

	// Gameworld stuffs
	std::vector<Level*> levels;
	Level* currentLevel;

	std::list<StaticSprite*> objects;
	std::list<Background*> backgrounds;

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
	void addSprite(StaticSprite *sprite);
	void addBackground(Background *sprite);
	void addLevel(Level* level);
	CommandManager& getCommandManager() { return cmdMgr; };
	void onQuitEvent(SDL_Event& event);
	void pause(const Uint8* kbState);
private:
	void input();
	void tickLevel();
	void renderLevel(SDL_Renderer * renderer);
	void close();
	void renderObjects();
	void tickObjects();
};

#endif
