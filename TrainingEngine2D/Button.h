#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include"Mouse.h"

class Button
{
public:
	static SDL_Texture* tex;
	bool selected = false;
	SDL_Rect srect, drect;
	//sounds?
	void update(Mouse* mouse);
	void draw(SDL_Renderer* ren);
	void setPos(int x, int y);
	Button(SDL_Renderer* ren, int, int);
	~Button();
};

