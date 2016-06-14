//ALbert Beranek CG programming
/////////////////////////////////////////////////////////////////////

#pragma once
//#include "GameManager.h"

const int SCREEN_WIDTH = 1465;
const int SCREEN_HEIGHT = 974;

extern SDL_Surface* gScreenSurface;

class SDLInit {
public:
	bool Setup();
	void Update();
	bool Load();
	void Close();
	SDL_Surface* loadFromFile(std::string path);
	void UpdateBackground();
	void ApplySurface(int x=0,int y=0,SDL_Surface* source=NULL,SDL_Surface*destination=NULL);
};

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
	SDL_Surface* loadFromRenderedText(std::string textureText, SDL_Color textColor);

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






