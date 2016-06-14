//ALbert Beranek CG programming
/////////////////////////////////////////////////////////////////////
#include "GameManager.h"

GameData gameData;

float fClock = 5.0f;
bool bNewPiece;

//Text
SDL_Surface* gTextSurfaceGDScore = NULL;
SDL_Surface* gTextSurfaceGDLevel = NULL;
SDL_Surface* gTextSurfaceGDMultiplier = NULL;
SDL_Surface* gTextSurfaceGDNxtLvl = NULL;

LTexture gTextTextureGDScore; 
LTexture gTextTextureGDLevel;
LTexture gTextTextureGDMultiplier;
LTexture gTextTextureGDNextLevel; 

SDLInit* sldInit;

bool GameData::Init() {
	bool succes = true;

	gameData.Score = 0;
	gameData.Level = 1;
	gameData.Multiplier = fClock;
	gameData.NxtLvl = 10;
	bNewPiece = true;

	return succes;
};
void GameData::Load() {
	SDL_Color textColorLvl = { 0,255,255 };

	std::string multi (std::to_string(gameData.Multiplier));
	multi.resize(3);

	gTextSurfaceGDScore = gTextTextureGDScore.loadFromRenderedText(std::to_string(gameData.Score), textColorLvl);
	gTextSurfaceGDLevel = gTextTextureGDLevel.loadFromRenderedText(std::to_string(gameData.Level), textColorLvl);
	gTextSurfaceGDScore = gTextTextureGDScore.loadFromRenderedText(std::to_string(gameData.Score), textColorLvl);
	gTextSurfaceGDNxtLvl = gTextTextureGDNextLevel.loadFromRenderedText(std::to_string(gameData.NxtLvl), textColorLvl);
	gTextSurfaceGDMultiplier = gTextTextureGDMultiplier.loadFromRenderedText(multi, textColorLvl);
};

void GameData::Update() {
	if (fClock <= 0.0f) {
		fClock = 0.0f;
	}
	else if (bNewPiece == true) {
		fClock = 5.0f;
	}

	sldInit->ApplySurface(1220, 450, gTextSurfaceGDScore, gScreenSurface);
	sldInit->ApplySurface(1170, 730, gTextSurfaceGDNxtLvl, gScreenSurface);
	sldInit->ApplySurface(1180, 160, gTextSurfaceGDLevel, gScreenSurface);
	sldInit->ApplySurface(210, 690, gTextSurfaceGDMultiplier, gScreenSurface);
};
