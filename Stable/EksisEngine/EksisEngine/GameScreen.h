#pragma once
#include "Screen.h"

class GameScreen : public Screen
{
public:
	GameScreen();
	~GameScreen();

	void Load();
	void Unload();
	void Update(double delta);
	void Render();
	void Input();
	void Shutdown();
	ScreenID GetID();

private:
	float radians;
	EVector position;
	ESquare player;
	ESquare platform;
	ESprite bank;
	ESprite asteroid;

};