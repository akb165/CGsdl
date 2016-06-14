//ALbert Beranek CG programming
/////////////////////////////////////////////////////////////////////
#pragma once
#include "GameManager.h"

class Entity {

protected:
	int xPos;
	int yPos;
};

class Cube: Entity {
public:
	int PointValue;
	int  Vel;
	bool Grouped;
	void Load();
	void Update();
	
};

//The dot that will move around on the screen
class Dot :Cube
{
public:
	//The dimensions of the dot
	static const int DOT_WIDTH = 43;
	static const int DOT_HEIGHT = 43;

	bool checkCollision(SDL_Rect a, SDL_Rect b);

	//Maximum axis velocity of the dot
	static const int DOT_VEL = 46;
	
	//Initializes the variables
	Dot();

	//Takes key presses and adjusts the dot's velocity
	void handleEvent(SDL_Event& e);

	//Moves the dot
	void move(SDL_Rect& wall);

	//Shows the dot on the screen
	void render();

private:
	//The X and Y offsets of the dot
	int mPosX, mPosY;

	//The velocity of the dot
	int mVelX, mVelY;

	//Dot's collision box
	SDL_Rect mCollider;
};
/*
CHaracteristics of tetris object

Moves: down, left, right
Speed: down (3x speed)
Slow: up (1/2 speed)

Required:
must move in grid.
most hold shape.

stuff I need to think about
keyboard commands for arrow keys and (awsd)
breaks apart when part of a line 10.
*/