#include "Mouse.h"

void Mouse::update()
{
	SDL_GetMouseState(&rect.x, &rect.y);
	//Point moves with mouse rectangle
	point.x = rect.x;
	point.y = rect.y;
}

void Mouse::draw(SDL_Renderer * ren)
{
	SDL_RenderCopy(ren, tex, NULL, &rect);
}

Mouse::Mouse(SDL_Renderer* ren)
{
	tex = IMG_LoadTexture(ren, "mouse.png");
	rect.x = rect.y = 0;
	rect.w = 11;
	rect.h = 15;
	SDL_ShowCursor(0); //Turn of showing system mouse
	point.x = point.y = 0;
	point.w = point.h = 1;

}

Mouse::~Mouse()
{
}
