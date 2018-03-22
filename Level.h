#ifndef LEVEL_H
#define LEVEL_H
#include <list>
#include "StaticSprite.h"
#include "Background.h"
#include <vector>
#include <unordered_map>


class Level {
private:
	std::string ident;
	std::vector<StaticSprite*> objects;
	std::vector<Background*> backgrounds;
	std::unordered_map<std::string, StaticSprite*> gui;
public:

	void addSprite(StaticSprite *sprite);
	void addBackground(Background *sprite);
	void addGui(std::string key, StaticSprite *sprite);

	Level(std::string ident);
	~Level();

	void init(SDL_Renderer * renderer);

	virtual void tick();
	void render(SDL_Renderer* renderer);

	void removeSprite(StaticSprite *spr);
	void removeGui(std::string key);


};

#endif