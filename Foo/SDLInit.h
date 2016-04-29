//ALbert Beranek CG programming
/////////////////////////////////////////////////////////////////////

#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <cmath>

//Screen dimension constants
const int SCREEN_WIDTH = 1465;
const int SCREEN_HEIGHT = 974;

class SDLInit {
public:
	bool Setup();
	void Update();
	bool Load();
};