#pragma once
#include "Screen.h"
#include "Player.h"
#include "Platform.h"
#include "Box.h"
class GameScreen : public Screen
{
public:
	GameScreen();
	~GameScreen();

	void Load();
	void Unload();
	void Update(double delta);
	void Render();
	void Input(EInput* input);
	void Shutdown();
	ScreenID GetID();

private:	
	Platform m_platform1;
	Platform m_platform2;
	Player m_player1;
	Box m_box1;
};