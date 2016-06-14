//ALbert Beranek CG programming
/////////////////////////////////////////////////////////////////////
#pragma once

//#include "GameManager.h"

class GameData {
public:
	int Score = 000000;
	int Level = 1;
	float Multiplier =0.0f;
	int NxtLvl = 10;
	bool Init();
	void Load();
	void Update();
};
