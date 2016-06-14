//ALbert Beranek CG programming
/////////////////////////////////////////////////////////////////////

#include "GameManager.h"

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image
extern SDL_Surface* loadSurface(std::string path);

//Current displayed PNG image
extern SDL_Surface* gPNGSurface;

GameManager  gManager;
int main(int argc, char* args[])
{
	if (!gManager.Init()) {
	}
	gManager.Update();

	return 0;
}