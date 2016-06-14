//ALbert Beranek CG programming
/////////////////////////////////////////////////////////////////////
#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include <time.h>
#include "Time.h"
#include "SDLInit.h"
#include "GameData.h"
#include "Character.h"


class GameManager {
public:
	bool Init();
	void Update();
	int Level = 0;
};