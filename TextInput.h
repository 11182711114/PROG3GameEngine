#ifndef TEXTINPUT_H
#define TEXTINPUT_H
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

class TextInput {

private:
	std::string text;
	bool acceptingInput;
	SDL_Color textColor = { 0, 0, 0, 0xFF };
	TTF_Font *font;
	int x;
	int y;
	int w;
	int h;

public:

	void accept();

	void render(SDL_Renderer* renderer);


	TextInput(TTF_Font* font, int x, int y, int w, int h);
	~TextInput();
};

#endif