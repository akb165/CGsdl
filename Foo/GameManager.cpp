//ALbert Beranek CG programming
/////////////////////////////////////////////////////////////////////
#include "GameManager.h"


Dot dot;
Cube gmcube;
GameData* gameData;
SDLInit* gmsdlInit;

bool GameManager::Init() {
	//Start up SDL and create window
	bool success = true;
	Dot dot;

	if (!gmsdlInit->Setup())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		
		//Load media
		if (!gmsdlInit->Load())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			if (!gameData->Init())
			{
				printf("Failed to initialize!\n");
			}
			else
			{
				gameData->Load();
				gmcube.Load();
			}

		}

	}

	return success;
}
void GameManager::Update() {
	bool quit = false;
	SDL_Event e;
	SDL_Rect wall;
	wall.x = 494;
	wall.y = 430;
	wall.w = 220;
	wall.h = 220;

	while (!quit) {
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			else {
				dot.handleEvent(e);
			}
			dot.move(wall);
		}
		gmsdlInit->UpdateBackground();
		
		gameData->Update();
		dot.render();
		gmsdlInit->Update();
	}
	gmsdlInit->Close();
}