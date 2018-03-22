#include "Level.h"



void Level::addSprite(StaticSprite *sprite) {
	objects.push_back(sprite);
}

void Level::addBackground(Background *sprite) {
	backgrounds.push_back(sprite);
}

void Level::addGui(std::string key, StaticSprite *sprite) {
	gui.insert({ key, sprite });
}

void Level::tick() {
	for (auto it = objects.begin(); it != objects.end(); ) {
		auto *spr = *it;
		if (spr->toBeDeletedStatus()) {
			it = objects.erase(it);
			delete spr;
		}
		else {
			spr->tick(objects);
			++it;
		}
	}
}

void Level::render(SDL_Renderer* renderer) {
	SDL_RenderClear(renderer);


	for (Background* back : backgrounds) {
		back->render(renderer);
	}

	for (StaticSprite* spr : objects) {
		spr->render(renderer);
	}

	for (auto pair : gui) {
		StaticSprite *value = pair.second;
		value->render(renderer);
	}

	SDL_RenderPresent(renderer);
}
void Level::removeSprite(StaticSprite * inSpr) {
	for (StaticSprite *spr : objects) {
		if (spr == inSpr)
			spr->markDelete();
	}
}
void Level::removeGui(std::string key) {
	gui.erase(key);
}
Level::Level(std::string ident): ident(ident) {}


Level::~Level() {}

void Level::init(SDL_Renderer* renderer) {
	for (StaticSprite* spr : objects) {
		spr->init(renderer);
	}
	for (Background* back : backgrounds) {
		back->init(renderer);
	}
}
