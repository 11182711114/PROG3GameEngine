//Using SDL and standard IO 
#include "CimpleBulletEngine.h"
#include <SDL.h> 
#include <iostream> 
#include "Action.h"


//	Constructors
//all args
CimpleBulletEngine::CimpleBulletEngine(int x, int y, int rr, std::string title) :
	SCREEN_WIDTH(x),
	SCREEN_HEIGHT(y),
	refreshRate(rr),
	windowTitle(title),
	cmdMgr(*new CommandManager((SCREEN_WIDTH / 2), SCREEN_HEIGHT - 100, SCREEN_WIDTH - (SCREEN_WIDTH / 4), 50))
{
};
//Copy
CimpleBulletEngine::CimpleBulletEngine(const CimpleBulletEngine & other) :
	CimpleBulletEngine(other.SCREEN_WIDTH,other.SCREEN_HEIGHT,other.refreshRate,other.windowTitle) {};
// Default constructor
CimpleBulletEngine::CimpleBulletEngine() :
	CimpleBulletEngine(640, 640, 60, "CimpleBulletEngine") {};
// deconstructor
CimpleBulletEngine::~CimpleBulletEngine() {
	if (window != NULL)
		SDL_DestroyWindow(window);
	if (renderer != NULL)
		SDL_DestroyRenderer(renderer);
	TTF_Quit();
	SDL_Quit();
}

int CimpleBulletEngine::start() {
	SDL_Surface* screenSurface = NULL;
		
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	} 
	else {
		if (TTF_Init() != 0) {
			printf("TTF could not initialize! TTF_Error: %s\n", TTF_GetError());
		}
		else {
			window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
			if (window == NULL) {
				printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			} else {
				screenSurface = SDL_GetWindowSurface(window);
				SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xff, 0xff, 0xff));
				SDL_UpdateWindowSurface(window);

				renderer = SDL_CreateRenderer(window, -1, 0);
				if (renderer == NULL) {
					printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
				}

				font = TTF_OpenFont("C:/Users/Fredrik/source/repos/cBH/media/arial.ttf", 25);

				cmdMgr.passRenderer(renderer);

				//Initiate sprites, i.e. get textures
				for (Level* lvl : levels) {
					lvl->init(renderer);
				}

				//Set first level
				currentLevel = levels.front();

				//events[SDL_QUIT] = new Action(this&, onQuitEvent);

				// Main loop prep
					// FPS interval
				const int tickInterval = 1000 / refreshRate;
				std::cout << "tickInterval: " << tickInterval << "ms" << std::endl;
					// Frame independant movement
				int loopPrevious = SDL_GetTicks();
				int loopCurrent = SDL_GetTicks();;

				// Main loop
				std::cout << "going into main loop" << std::endl;
				while (!quit) {
					// Frame independent movement
					loopPrevious = loopCurrent;
					loopCurrent = SDL_GetTicks();
					// Loop delay
					int nextTick = SDL_GetTicks() + tickInterval;

					timeDiff = loopCurrent - loopPrevious;
					// Main loop calls
					if (!paused)
						tickLevel();
					renderLevel(renderer);

					input();

					// Delay appropriatly to desired fps
					int delay = nextTick - SDL_GetTicks();
					if (delay > 0)
						SDL_Delay(delay);
				}
			}
		}
	}
	return 0;
}

SDL_Renderer* CimpleBulletEngine::getRenderer() {
	return renderer;
}

void CimpleBulletEngine::input() {
	cmdMgr.tick(paused);
}

void CimpleBulletEngine::tickLevel() {
	currentLevel->tick();
}

void CimpleBulletEngine::renderLevel(SDL_Renderer* renderer) {
	currentLevel->render(renderer);
}

void CimpleBulletEngine::tickObjects() {
	for (StaticSprite* spr : objects) {
		//spr->tick(objects);
	}
}

void CimpleBulletEngine::renderObjects() {
	SDL_RenderClear(renderer);


	for (Background* back : backgrounds) {
		back->render(renderer);
	}

	for (StaticSprite* spr : objects) {
		spr->render(renderer);
	}

	SDL_RenderPresent(renderer);
}

// Is this necessary?
void CimpleBulletEngine::close() {
	for (StaticSprite* spr : objects) {
		SDL_Texture* texture = spr->getTexture();
		if (texture != NULL)
			SDL_DestroyTexture(texture);
	}
}

void CimpleBulletEngine::addLevel(Level * level) {
	levels.push_back(level);
	level->addGui("editbox", cmdMgr.getTextInput());
}

void CimpleBulletEngine::onQuitEvent(SDL_Event& event) {
	if (event.type == SDL_QUIT) {
		std::cout << "quitting" << std::endl;
		quit = true;
	}
}

void CimpleBulletEngine::pause(const Uint8* kbState) {
	std::cout << (!paused ? "paused" : "unpaused") << std::endl;

	if (!paused) {
	
		std::string pausedText = "PAUSED";

		SDL_Color textColor = { 0xFF, 0, 0, 0 }; // Full red
		SDL_Surface *surface = TTF_RenderText_Blended(font, pausedText.c_str(), textColor);
		SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

		int w, h;
		SDL_QueryTexture(texture, NULL, NULL, &w, &h);

		StaticSprite *pausedSpr = new StaticSprite((SCREEN_WIDTH / 2) - (w / 2), (SCREEN_HEIGHT / 2) - (h / 2), 0, 0, w, h, texture);
		currentLevel->addGui("paused", pausedSpr);

		SDL_FreeSurface(surface);
	} else {
		currentLevel->removeGui("paused");
	}
	paused = !paused;
}

