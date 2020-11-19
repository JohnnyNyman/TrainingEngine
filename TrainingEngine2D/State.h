#pragma once
#include<SDL.h>
#include<iostream>
#include"Mouse.h"
#include"Button.h"
#include"noise.h"
#include"noiseutils/noiseutils.h"
#include"TextureManager.h"

class State
{
public:
	static Mouse* mouse;
	static SDL_Window* win;
	static SDL_Renderer* ren;
	SDL_Texture* backgroundTexture;
	SDL_Texture* mapTexture;
	static State* current, *menu, *create, *generate;
	SDL_Event event;
	bool running = false;

	virtual void enter() = 0;
	virtual void update() = 0;
	virtual void exit() = 0;
	State();
	virtual ~State();

private:

};

class  Menu :public State
{
public:
	Button* createButton;
	Menu();
	~Menu();
	void enter();
	void update();
	void exit();
};

class Create:public State
{
public:
	Button* menuButton;
	Button* generateButton;
	Create();
	~Create();
	void enter();
	void update();
	void exit();

private:

};

class Generate :public State
{
public:
	Generate();
	~Generate();
	void enter();
	void update();
	void exit();
};





