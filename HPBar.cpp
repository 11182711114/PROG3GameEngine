#include "HPBar.h"



HPBar::HPBar(int x, int y, Position &otherPos, int sizeX, int sizeY, std::string imagePath, int w, int h, SDL_Color fgColor, SDL_Color bgColor) :
	GUIElement(
		x,
		y,
		otherPos,
		sizeX,
		sizeY,
		imagePath),
	w(w),
	h(h),
	bgColor(bgColor),
	fgColor(fgColor)
{}


HPBar::~HPBar() {}

void HPBar::render(SDL_Renderer * renderer) {
	int Percent = Percent > 1.f ? 1.f : Percent < 0.f ? 0.f : Percent;
	SDL_Color old;
	SDL_GetRenderDrawColor(renderer, &old.r, &old.g, &old.g, &old.a);
	SDL_Rect bgrect = { pos.getPositionXAsInt(), pos.getPositionYAsInt(), w, h };
	SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
	SDL_RenderFillRect(renderer, &bgrect);
	SDL_SetRenderDrawColor(renderer, fgColor.r, fgColor.g, fgColor.b, fgColor.a);
	int pw = (int) ((float) w * Percent);
	int px = pos.getPositionXAsInt() + (w - pw);
	SDL_Rect fgrect = { px, pos.getPositionYAsInt(), pw, h };
	SDL_RenderFillRect(renderer, &fgrect);
	SDL_SetRenderDrawColor(renderer, old.r, old.g, old.b, old.a);
}
