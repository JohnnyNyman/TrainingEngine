#include"State.h"
#include<SDL_image.h>

SDL_Window* State::win = 0;
SDL_Renderer* State::ren = 0;
State* State::current = 0;
State* State::menu = 0;
State* State::create = 0;
State* State::generate = 0;
Mouse* State::mouse = 0;

SDL_Rect* sRect, dRect;

State::State()
{
	if (!win) //only happens once
	{
		win = SDL_CreateWindow("State Machine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, NULL);
		ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
		mouse = new Mouse(ren);
	}
}

State::~State()
{

}

#pragma region MenuRegion
Menu::Menu()
{
	backgroundTexture = IMG_LoadTexture(ren, "MenuBackground.png");
	createButton = new Button(ren, 0, 32);
	createButton->setPos(1280 / 2 - (96 / 2), 200);
}

Menu::~Menu()
{
	delete createButton;
}

void Menu::enter()
{
	//start up the music
	//center the mouse cursor on screen?

	running = true;
}

void Menu::update()
{
	//get input
	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				SDL_Quit();
				std::exit(0); //bad form
			case SDL_MOUSEBUTTONUP:
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					if (createButton->selected)
					{
						current = create;
						running = false;
						break;
					}
				}
			}//end switch
		}//end poll loop
		mouse->update();
		createButton->update(mouse);
		SDL_RenderClear(ren);

		SDL_RenderCopy(ren, backgroundTexture, NULL, NULL);
		createButton->draw(ren);
		mouse->draw(ren);
		SDL_RenderPresent(ren);
	}//end main loop


}

void Menu::exit()
{
	//disable mouse?
	//stop music?
}
#pragma endregion


#pragma region CreateRegion
Create::Create()
{
	backgroundTexture = IMG_LoadTexture(ren, "MenuBackground.png");
	menuButton = new Button(ren, 0, 64);
	menuButton->setPos(250 / 2 - (96 / 2), 650);
	generateButton = new Button(ren, 0, 128);
	generateButton->setPos(250 / 2 - (96 / 2), 100);



}

Create::~Create()
{
	delete menuButton;
	delete generateButton;
	delete mapTexture;
}

void Create::enter()
{
	running = true;
	mapTexture = TextureManager::LoadTexture("tutorial.bmp", ren);
	dRect.w = 512;
	dRect.h = 512;

	dRect.x = 200;
	dRect.y = 50;
}

void Create::update()
{
	//get input
	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				SDL_Quit();
				std::exit(0); //bad form
			case SDL_MOUSEBUTTONUP:
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					if (menuButton->selected)
					{
						current = menu;
						running = false;
						break;
					}

					if (generateButton->selected)
					{
						current = generate;
						running = false;
						break;
					}
				}
			}//end switch
		}//end poll loop
		mouse->update();
		menuButton->update(mouse);
		generateButton->update(mouse);
		SDL_RenderClear(ren);


		SDL_RenderCopy(ren, backgroundTexture, NULL, NULL);
		SDL_RenderCopy(ren, mapTexture, NULL, &dRect);
		menuButton->draw(ren);
		generateButton->draw(ren);
		mouse->draw(ren);
		SDL_RenderPresent(ren);
	}//end main loop
}

void Create::exit()
{
}
#pragma endregion

#pragma region GenerateRegion
Generate::Generate()
{
	backgroundTexture = IMG_LoadTexture(ren, "player_anims.png");
}

Generate::~Generate()
{
}

void Generate::enter()
{
	running = true;
}

void Generate::update()
{
	while (running)
	{
		/*
		module::Perlin myModule;
		myModule.SetOctaveCount(6); //Amount of detail
		myModule.SetFrequency(1.0); //Number of terrain features
		myModule.SetPersistence(0.5); //Roughness
		utils::NoiseMap heightMap;
		utils::NoiseMapBuilderPlane heightMapBuilder;
		heightMapBuilder.SetSourceModule(myModule);
		heightMapBuilder.SetDestNoiseMap(heightMap);
		//Noise map size
		heightMapBuilder.SetDestSize(256, 256);
		//Set bounding rectangle (x,y)coordinates lower-x, upper-x, lower-z, and upper-z in graph
		//See image Assets/heightmapgraph.png
		heightMapBuilder.SetBounds(6.0, 10.0, 1.0, 5.0);
		heightMapBuilder.Build();

		//Rendering terrain height map
		utils::RendererImage renderer;
		utils::Image image;
		renderer.SetSourceNoiseMap(heightMap);
		renderer.SetDestImage(image);
		renderer.ClearGradient();
		renderer.AddGradientPoint(-1.0000, utils::Color(0, 0, 128, 255)); // deeps
		renderer.AddGradientPoint(-0.2500, utils::Color(0, 0, 255, 255)); // shallow
		renderer.AddGradientPoint(0.0000, utils::Color(0, 128, 255, 255)); // shore
		renderer.AddGradientPoint(0.0625, utils::Color(240, 240, 64, 255)); // sand
		renderer.AddGradientPoint(0.1250, utils::Color(32, 160, 0, 255)); // grass
		renderer.AddGradientPoint(0.5750, utils::Color(224, 224, 0, 255)); // dirt
		renderer.AddGradientPoint(0.8500, utils::Color(128, 128, 128, 255)); // rock
		renderer.AddGradientPoint(1.0000, utils::Color(255, 255, 255, 255)); // snow
		renderer.EnableLight();
		renderer.SetLightContrast(3.0); //Contrast
		renderer.SetLightBrightness(1.5); //Brightness
		renderer.Render();

		//Writing image to outputfile (.bmp)
		utils::WriterBMP writer;
		writer.SetSourceImage(image);
		writer.SetDestFilename("tutorial.bmp");
		writer.WriteDestFile();
		*/

		module::RidgedMulti mountainTerrain;

		module::Billow baseFlatTerrain;
		baseFlatTerrain.SetFrequency(2.0);

		module::ScaleBias flatTerrain;
		flatTerrain.SetSourceModule(0, baseFlatTerrain);
		flatTerrain.SetScale(0.125); //Scaling the noise between 0 to 1
		flatTerrain.SetBias(-0.75); //-0.75 lowers the elevation of the lumps by ca. -1

		//Control Module
		module::Perlin terrainType;
		terrainType.SetFrequency(0.5);
		terrainType.SetPersistence(0.25);

		//Selector Module
		module::Select terrainSelector;
		terrainSelector.SetSourceModule(0, flatTerrain);
		terrainSelector.SetSourceModule(1, mountainTerrain);
		terrainSelector.SetControlModule(terrainType);
		terrainSelector.SetBounds(0.0, 1000.0);
		terrainSelector.SetEdgeFalloff(0.125); //Smoothes the edge between terrain types

		//Creates less ordered output
		module::Turbulence finalTerrain;
		finalTerrain.SetSourceModule(0, terrainSelector);
		finalTerrain.SetFrequency(6.0); //noisy
		finalTerrain.SetPower(0.05); //ropey

		utils::NoiseMap heightMap;
		utils::NoiseMapBuilderPlane heightMapBuilder;
		heightMapBuilder.SetSourceModule(finalTerrain);
		heightMapBuilder.SetDestNoiseMap(heightMap);
		heightMapBuilder.SetDestSize(512, 512); //256, 256
		heightMapBuilder.SetBounds(6.0, 10.0, 1.0, 5.0); //2.0, 6.0, 1.0, 5.0 | 6.0, 10.0, 1.0, 5.0
		heightMapBuilder.Build();

		utils::RendererImage renderer;
		utils::Image image;
		renderer.SetSourceNoiseMap(heightMap);
		renderer.SetDestImage(image);
		renderer.ClearGradient();
		//renderer.AddGradientPoint(-1.00, utils::Color(32, 160, 0, 255)); // grass
		//renderer.AddGradientPoint(-0.25, utils::Color(224, 224, 0, 255)); // dirt
		//renderer.AddGradientPoint(0.25, utils::Color(128, 128, 128, 255)); // rock
		//renderer.AddGradientPoint(1.00, utils::Color(255, 255, 255, 255)); // snow
		renderer.AddGradientPoint(-1.0000, utils::Color(0, 0, 128, 255)); // deeps
		renderer.AddGradientPoint(-0.6500, utils::Color(0, 0, 255, 255)); // shallow
		renderer.AddGradientPoint(-0.5300, utils::Color(0, 128, 255, 255)); // shore
		renderer.AddGradientPoint(-0.3600, utils::Color(240, 240, 64, 255)); // sand
		renderer.AddGradientPoint(-0.3300, utils::Color(32, 160, 0, 255)); // grass
		renderer.AddGradientPoint(0.5750, utils::Color(107, 88, 76, 255)); // dirt
		renderer.AddGradientPoint(0.8500, utils::Color(128, 128, 128, 255)); // rock
		renderer.AddGradientPoint(1.0000, utils::Color(255, 255, 255, 255)); // snow
		renderer.EnableLight();
		renderer.SetLightContrast(3.0);
		renderer.SetLightBrightness(2.0);
		renderer.Render();

		utils::WriterBMP writer;
		writer.SetSourceImage(image);
		writer.SetDestFilename("tutorial.bmp");
		writer.WriteDestFile();


		current = create;
		running = false;
		break;
	}
}

void Generate::exit()
{
}
#pragma endregion