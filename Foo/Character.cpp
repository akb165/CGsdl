//ALbert Beranek CG programming
/////////////////////////////////////////////////////////////////////
#include "GameManager.h"

Cube cube;

SDL_Surface* gPNGTetris = NULL;
SDL_Surface* gPNGTetris1 = NULL;
//LTexture* gTextTetris = NULL;

SDLInit* crsdlInit;

bool checkCollision(SDL_Rect a, SDL_Rect b);

void Cube::Load() {
	gPNGTetris = crsdlInit->loadFromFile("Images/TetrisPiece.png");
	
}

void Cube::Update() {
	
}
//X|498|544|590|631|676|721|765|810|855|899|
//Y|62|108|154|200|246|292|338|384|430|476|522|568|614|660|706|752|798|844|890|
Dot::Dot() {
	//Initialize offets
	mPosX = 498;
	mPosY = 62;

	//Initialize Velocity
	mVelX = 0;
	mVelY = 0;
}

void Dot::handleEvent(SDL_Event& e) {
	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		//adjust velocity
		switch (e.key.keysym.sym) {
			case SDLK_UP:mVelY -= DOT_VEL; break;
			case SDLK_DOWN:mVelY += DOT_VEL; break;
			case SDLK_LEFT:mVelX -= DOT_VEL; break;
			case SDLK_RIGHT:mVelX += DOT_VEL; break;
		}
	}
	else if (e.type == SDL_KEYUP&&e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
		case SDLK_UP:mVelY += DOT_VEL; break;
		case SDLK_DOWN:mVelY -= DOT_VEL; break;
		case SDLK_LEFT:mVelX += DOT_VEL; break;
		case SDLK_RIGHT:mVelX -= DOT_VEL; break;
		}
	}
}


void Dot::move(SDL_Rect& wall) {
	mCollider.x = mPosX;
	mCollider.y = mPosY;
	mCollider.w = DOT_WIDTH;
	mCollider.h = DOT_HEIGHT;

	mPosX += mVelX; //move left or right
	mCollider.x = mPosX;
	//if dot went to far
	if ((mPosX<=497) || (mPosX >= 899+ DOT_WIDTH) || checkCollision(mCollider, wall)) {
		mPosX -= mVelX;
	}
	
	mPosY += mVelY;
	mCollider.y = mPosY;
	//if dot went to far
	if ((mPosY<=61) || (mPosY >= 891+ DOT_HEIGHT || checkCollision(mCollider, wall))) {
		mPosY -= mVelY;
		mCollider.y = mPosY;
	}
}

void Dot::render() {
	//SHow the dot
	crsdlInit->ApplySurface(mPosX, mPosY, gPNGTetris, gScreenSurface);
}


bool Dot::checkCollision(SDL_Rect a, SDL_Rect b) {
	if ((a.x >= b.x) && (a.x <= (b.x + b.w)) && (a.y >= b.y) && (a.y <= (b.x + b.w))) return true;
		return false;
}