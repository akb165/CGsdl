//ALbert Beranek CG programming
/////////////////////////////////////////////////////////////////////

#include "SDLInit.h"

//Texture wrapper class
class LTexture {
public:
	//Init varibles
	LTexture();

	//Deallocate memory
	~LTexture();

	//Loads image at specified Path
	bool loadFromFile(std::string path);

	//Create image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor);

	//Deallocates texture
	void free();

	//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(Uint8 alpha);

	//Renders texture at given point
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Gets image dimensions
	int getWidth();
	int getHeight();

private:
	//The actual hardware texture
	SDL_Texture* mTexture;

	//Image dimensions
	int mWidth;
	int mHeight;
};

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image
extern SDL_Surface* loadSurface(std::string path);

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

//Rendered texture
LTexture gTextTexture;

LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile(std::string path)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}

	//Return success
	return mTexture != NULL;
}

void LTexture::free()
{
	//Free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture rgb
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}
bool init()
{

	//Initialization flag
	bool success = true;

	////Initialize SDL
	//if (SDL_Init(SDL_INIT_VIDEO) < 0)
	//{
	//	printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
	//	success = false;
	//}
	//else
	//{
	//	//Create window
	//	gWindow = SDL_CreateWindow("Tetris Twist", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	//	if (gWindow == NULL)
	//	{
	//		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
	//		success = false;
	//	}
	//	else
	//	{
	//		//Initialize PNG loading
	//		int imgFlags = IMG_INIT_PNG;
	//		if (!(IMG_Init(imgFlags) & imgFlags))
	//		{
	//			printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
	//			success = false;
	//		}
	//		else
	//		{
	//			//Get window surface
	//			gScreenSurface = SDL_GetWindowSurface(gWindow);
	//		}

	//		//Initialize SDL_ttf
	//		if (TTF_Init() == -1)
	//		{
	//			printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
	//			success = false;
	//		}
	//	}
	//}

	return success;
}

bool loadMedia()
{
	////Loading success flag
	//bool success = true;

	////Load PNG surface
	//gPNGSurface = loadSurface("LevelBackground.png");
	//if (gPNGSurface == NULL)
	//{
	//	printf("Failed to load PNG image!\n");
	//	success = false;
	//}

	////Open the font
	//gFont = TTF_OpenFont("lazy.ttf", 28);
	//if (gFont == NULL) {
	//	printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
	//	success = false;
	//}
	//else {
	//	SDL_Color textColor = { 0,0,0 };
	//	if (!gTextTexture.loadFromRenderedText("next", textColor)) {
	//		printf("Failed to render text texture!\n");
	//		success = false;
	//	}
	//}

	//return success;
}

void close()
{
	//Free loaded image
	SDL_FreeSurface(gPNGSurface);
	gPNGSurface = NULL;

	//Free global font
	TTF_CloseFont(gFont);
	gFont = NULL;

	//Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

SDL_Surface* loadSurface(std::string path)
{
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, NULL);
		if (optimizedSurface == NULL)
		{
			printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return optimizedSurface;
}

int main(int argc, char* args[])
{
	////Start up SDL and create window
	//SDLInit sdlInit;

	//if (!sdlInit.Setup())
	//{
	//	printf("Failed to initialize!\n");
	//}
	//else
	//{
	//	//Load media
	//	if (!loadMedia())
	//	{
	//		printf("Failed to load media!\n");
	//	}
	//	else
	//	{
	//		////Main loop flag
	//		//bool quit = false;

	//		////Event handler
	//		//SDL_Event e;

	//		//While application is running
	//		//while (!quit)
	//		//{
	//		//	//Handle events on queue
	//		//	while (SDL_PollEvent(&e) != 0)
	//		//	{
	//		//		//User requests quit
	//		//		if (e.type == SDL_QUIT)
	//		//		{
	//		//			quit = true;
	//		//		}
	//		//	}

	//		//	//Apply the PNG image
	//		//	SDL_BlitSurface(gPNGSurface, NULL, gScreenSurface, NULL);

	//		//	//Update the surface
	//		//	SDL_UpdateWindowSurface(gWindow);

	//		//	//Clear screen
	//		//	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	//		//	SDL_RenderClear(gRenderer);

	//		//	//Render current frame
	//		//	gTextTexture.render((SCREEN_WIDTH - gTextTexture.getWidth()) / 2, (SCREEN_HEIGHT - gTextTexture.getHeight()) / 2);

	//		//	//Update screen
	//		//	SDL_RenderPresent(gRenderer);

	//		//}
	//	}
	//}

	////Free resources and close SDL
	//close();

	return 0;
}