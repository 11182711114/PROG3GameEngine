#include "TextInput.h"



void TextInput::accept() {
	SDL_Event e;

	SDL_StartTextInput();

	while (acceptingInput) {
		while (SDL_PollEvent(&e) != 0) {
			switch (e.type) {
			case SDL_KEYDOWN:
				if (e.key.keysym.sym == SDLK_BACKSPACE && text.length() > 0)
					text.pop_back();
			case SDL_TEXTINPUT:
				text += e.text.text;
				break;
			case SDL_TEXTEDITING:
				break;
			}
		}
	}
}

void TextInput::render(SDL_Renderer * renderer) {
	if (acceptingInput) {
		std::string toRender = "> " + text;
		SDL_Surface *surface = TTF_RenderText_Solid(font, toRender.c_str(), textColor);
		SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
		
		SDL_QueryTexture(texture, NULL, NULL, &w, &h);

		SDL_Rect rect = { 100,100, x, y };

		SDL_RenderCopy(renderer, texture, NULL, &rect);

		SDL_FreeSurface(surface);
		SDL_DestroyTexture(texture);

		
	}
	
}


TextInput::TextInput(TTF_Font * font, int x, int y, int w, int h): 
	font(font), x(x), y(y), w(w), h(h) {}

TextInput::~TextInput() {}
