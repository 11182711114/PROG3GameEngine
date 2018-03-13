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
	windowTitle(title) 
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
	SDL_Quit();
}

int CimpleBulletEngine::start() {
	SDL_Surface* screenSurface = NULL;
		
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else {
		window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else {
			screenSurface = SDL_GetWindowSurface(window);
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xff, 0xff, 0xff));
			SDL_UpdateWindowSurface(window);

			renderer = SDL_CreateRenderer(window, -1, 0);
			if (renderer == NULL) {
				printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			}

			//Initiate sprites, i.e. get textures
			for (Sprite* spr : objects) {
				spr->init(renderer);
			}
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
				tickObjects();
				renderObjects();
				input();

				// Delay appropriate to desired fps
				int delay = nextTick - SDL_GetTicks();
				if (delay > 0)
					SDL_Delay(delay);
			}
		}
	}
	return 0;
}

void CimpleBulletEngine::input() {
	cmdMgr.tick();
}

void CimpleBulletEngine::tickObjects() {
	for (Sprite* spr : objects) {
		spr->tick(objects);
	}
}

void CimpleBulletEngine::renderObjects() {
	SDL_RenderClear(renderer);

	for (Sprite* spr : objects) {
		spr->render(*renderer);
	}
	SDL_RenderPresent(renderer);
}

// Is this necessary?
void CimpleBulletEngine::close() {
	for (Sprite* spr : objects) {
		SDL_Texture* texture = spr->getTexture();
		if (texture != NULL)
			SDL_DestroyTexture(texture);
	}
}

void CimpleBulletEngine::addSprite(Sprite * sprite) {
	objects.push_back(sprite);
}

void CimpleBulletEngine::onQuitEvent(SDL_Event& event) {
	if (event.type == SDL_QUIT) {
		std::cout << "quitting" << std::endl;
		quit = true;
	}
}
;
