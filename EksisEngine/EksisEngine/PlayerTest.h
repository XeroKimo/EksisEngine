#pragma once
#include "EngineFiles.h"
#include "CameraTest.h"

class Player
{
public:
	Player();
	
	void Update(double delta);
	void Render();
	void Input();
	void SetID(int id);
	ESquare& GetSquare();
private:
	ESquare player;
};