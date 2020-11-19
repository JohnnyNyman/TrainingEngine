#pragma once
#include <SDL.h>
#include<SDL_image.h>
class Mouse
{
public:
	SDL_Texture* tex;
	SDL_Rect rect;
	SDL_Rect point;
	void update();
	void draw(SDL_Renderer* ren);
	Mouse(SDL_Renderer* ren);
	~Mouse();
};

