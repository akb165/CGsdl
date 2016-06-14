//ALbert Beranek CG programming
/////////////////////////////////////////////////////////////////////

#include "GameManager.h"

SDLInit* sdlInit;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//Current displayed PNG image
SDL_Surface* gPNGSurface = NULL;

//Text
SDL_Surface* gTextSurfaceNxt = NULL;
SDL_Surface* gTextSurfaceLVL = NULL;
SDL_Surface* gTextSurfaceScr = NULL;
SDL_Surface* gTextSurfaceNxtLvl = NULL;
SDL_Surface* gTextSurfaceActLvl = NULL;
SDL_Surface* gTextSurfaceMtplr = NULL;
SDL_Surface* gPNGDot = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Globally used font
TTF_Font *gFont = NULL;

//Rendered texture
LTexture gPNGTexture;
LTexture gTextTextureNext; //Text for Next FIeld
LTexture gTextTextureLevel; //Text for Level Field
LTexture gTextTextureScore;//Text for Score
LTexture gTextTextureNextLevel; //Text for Level Field
LTexture gTextTextureMulripler;
LTexture gPressTexture;
LTexture gUpTexture;
LTexture gDownTexture;
LTexture gLeftTexture;
LTexture gRightTexture;

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

SDL_Surface* LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
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
		
		return textSurface;
	}

	//Return success
	return textSurface;
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

bool SDLInit::Setup() 
	{
		//Initialization flag
		bool success = true;

		//Initialize SDL
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Set texture filtering to linear
			if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
			{
				printf("Warning: Linear texture filtering not enabled!");
			}

			//Create window
			gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
			if (gWindow == NULL)
			{
				printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Create vsynced renderer for window
				gRenderer = SDL_CreateRenderer(gWindow, -1,  SDL_RENDERER_ACCELERATED);
				if (gRenderer == NULL)
				{
					printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
					success = false;
				}
				else
				{
					//Initialize renderer color
					SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

					//Initialize PNG loading
					int imgFlags = IMG_INIT_PNG;
					if (!(IMG_Init(imgFlags) & imgFlags))
					{
						printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
						success = false;
					}	else
					{
						//Get window surface
						gScreenSurface = SDL_GetWindowSurface(gWindow);
					}

					//Initialize SDL_ttf
					if (TTF_Init() == -1)
					{
						printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
						success = false;
					}
				}
			}
		}

		return success;
	}

SDL_Surface* SDLInit::loadFromFile(std::string path){
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

	void SDLInit::UpdateBackground() {
		SDLInit::ApplySurface(0, 0, gPNGSurface, gScreenSurface);
	}

void SDLInit::Update() {

	//Current rendered texture
	LTexture* currentTexture = NULL;


			//Apply the PNG image
			SDLInit::ApplySurface(1120, 80, gTextSurfaceLVL, gScreenSurface);
			SDLInit::ApplySurface(190, 110, gTextSurfaceNxt, gScreenSurface);
			SDLInit::ApplySurface(1110, 350, gTextSurfaceScr, gScreenSurface);
			SDLInit::ApplySurface(1120, 600, gTextSurfaceNxtLvl, gScreenSurface);
			SDLInit::ApplySurface(1110, 660, gTextSurfaceLVL, gScreenSurface);
			SDLInit::ApplySurface(125, 600, gTextSurfaceMtplr, gScreenSurface);

			SDL_UpdateWindowSurface(gWindow);
}

bool SDLInit::Load() {
	//Loading success flag
	bool success = true;

	//Load Background
	gPNGSurface = sdlInit->loadFromFile("Images/LevelBackground.png");
	if (gPNGSurface == NULL)
	{
		printf("Failed to load press texture!\n");
		success = false;
	}

	gFont = TTF_OpenFont("Mecha_Bold.ttf", 72);
	if (gFont == NULL) {
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else {

		SDL_Color textColorLvl = { 0,255,255 };
		SDL_Color textColorNxt = { 0,255,0 };
		gTextSurfaceLVL = gTextTextureLevel.loadFromRenderedText("Level", textColorLvl);
		gTextSurfaceNxt = gTextTextureNext.loadFromRenderedText("Next", textColorNxt);
		gTextSurfaceScr = gTextTextureScore.loadFromRenderedText("Score", textColorLvl);
		gTextSurfaceNxtLvl = gTextTextureNextLevel.loadFromRenderedText("Next", textColorLvl);
		gTextSurfaceMtplr = gTextTextureMulripler.loadFromRenderedText("Multiplier", textColorLvl);
	}
	return success;
}
void SDLInit::Close()
{
	//Free loaded image
	SDL_FreeSurface(gPNGSurface);
	gPNGSurface = NULL;
	SDL_FreeSurface(gTextSurfaceLVL);
	gTextSurfaceLVL = NULL;
	SDL_FreeSurface(gTextSurfaceNxt);
	gTextSurfaceNxt = NULL;
	SDL_FreeSurface(gTextSurfaceScr);
	gTextSurfaceScr = NULL;
	SDL_FreeSurface(gTextSurfaceNxtLvl);
	gTextSurfaceNxtLvl = NULL;
	SDL_FreeSurface(gPNGDot);
	gPNGDot = NULL;

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

void SDLInit::ApplySurface(int x, int y, SDL_Surface* source, SDL_Surface* destination) {
	//Make temporary rectangle
	SDL_Rect offset;

	//give the offsets
	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(source, NULL, destination, &offset);
}