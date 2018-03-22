#include "TextInput.h"
#include <iostream>



void TextInput::tick(std::vector<StaticSprite*> otherObj) {
	if (active) {
		font = TTF_OpenFont("C:/Users/Fredrik/source/repos/cBH/media/arial.ttf", 25);

		SDL_Event e;
		std::cout << "accepting input" << std::endl;
		acceptingInput = true;
		SDL_StartTextInput();

		while (SDL_PollEvent(&e) != 0) {
			std::cout << "text is: " << text << std::endl;
			std::cout << "Polled event: " << e.key.keysym.sym << std::endl;
			switch (e.type) {
			case SDL_KEYDOWN:
				if (e.key.keysym.sym == SDLK_BACKSPACE && text.length() > 0)
					text.pop_back();
				else if (e.key.keysym.sym == SDLK_RETURN) {
					SDL_StopTextInput();
					goto afterPolling;
				}
				break;
			case SDL_TEXTINPUT:
				std::cout << "input: " << e.text.text << " from key " << e.key.keysym.sym << std::endl;
				text += e.text.text;
				break;
			case SDL_TEXTEDITING:
				break;
			}
			refreshTexture();
		}
	afterPolling:
		std::cout << "stopped accepting input" << std::endl;
	}
}

void TextInput::refreshTexture() {
	if (acceptingInput) {
		std::cout << "Rendering text input" << std::endl;
		std::string toRender = "> " + text;
		SDL_Surface *surface = TTF_RenderText_Solid(font, toRender.c_str(), textColor);
		SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
		
		SDL_QueryTexture(texture, NULL, NULL, &sizeX, &sizeY);
		SDL_DestroyTexture(StaticSprite::getTexture());
		
		setTexture(texture);

		//SDL_Rect rect = { x,y, w, h };

		//SDL_RenderCopy(renderer, texture, NULL, &rect);

		//SDL_FreeSurface(surface);
		//SDL_DestroyTexture(texture);
	}
}

void TextInput::setRenderer(SDL_Renderer * renderer) {
	this->renderer = renderer;
}

void TextInput::toggleActive() {
	if (!((int)(SDL_GetTicks() - lastCalled) >= cooldown))
		return;
	active = !active;
	lastCalled = SDL_GetTicks();
}


TextInput::TextInput(int x, int y, int sizeX, int sizeY):
	StaticSprite(x,y, 0, 0, sizeX, sizeY,NULL) {
}

TextInput::~TextInput() {}
