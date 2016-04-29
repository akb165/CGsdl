#include "GameManager.h"
#include "SDLInit.h"

//The window we'll be rendering to
extern SDL_Window* gWindow;

//The surface contained by the window
extern SDL_Surface* gScreenSurface;

//Current displayed PNG image
extern SDL_Surface* gPNGSurface;

//The window renderer
extern SDL_Renderer* gRenderer = NULL;

//Globally used font
extern TTF_Font *gFont = NULL;

bool GameManager::Init() {
	//Start up SDL and create window
	SDLInit sdlInit;

	if (!sdlInit.Setup())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{

		}
	close();
}
void GameManager::Update() {

}