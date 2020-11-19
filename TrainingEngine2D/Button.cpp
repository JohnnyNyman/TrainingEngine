#include "Button.h"

SDL_Texture* Button::tex = 0;
Button::Button(SDL_Renderer * ren, int x, int y)
{
	if (!tex)//only once
	{
		tex = IMG_LoadTexture(ren, "MenuButtons.png");
	}
	//Source
	srect.h = 32;
	srect.w = 96;
	//Destination
	drect.h = 32;
	drect.w = 96;

	srect.x = x;
	srect.y = y;
}

void Button::update(Mouse* mouse)
{
	selected = false;
	if (SDL_HasIntersection(&mouse->point, &drect))
	{
		selected = true;
		//Play sound?
		srect.x = 96;
	}
	else
	{
		srect.x = 0;
	}
}

void Button::draw(SDL_Renderer * ren)
{
	SDL_RenderCopy(ren, tex, &srect, &drect);
}

void Button::setPos(int x, int y)//setting the destination
{
	drect.x = x;
	drect.y = y;
}

Button::~Button()
{
}
