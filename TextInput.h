#ifndef TEXTINPUT_H
#define TEXTINPUT_H
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include "StaticSprite.h"

class TextInput: public StaticSprite {

private:
	std::string text;
	bool acceptingInput;
	SDL_Color textColor = { 0xFF, 0, 0, 0xFF }; 
	TTF_Font *font;

	bool active;

	SDL_Renderer *renderer = nullptr;

	// To prevent it from instantly going back into accepting text input
	int cooldown = 250;
	Uint32 lastCalled = 0;
	
	void refreshTexture();
public:

	void tick(std::vector<StaticSprite*> otherObj);
	void setRenderer(SDL_Renderer *renderer);
	void toggleActive();
	
	TextInput(int x, int y, int sizeX, int sizeY);
	~TextInput();
};

#endif