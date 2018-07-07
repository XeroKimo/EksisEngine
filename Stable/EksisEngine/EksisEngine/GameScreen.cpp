#include "GameScreen.h"

GameScreen::GameScreen()
{

}

GameScreen::~GameScreen()
{
}

void GameScreen::Load()
{
	LoadTexture(L"Bank.png");
	LoadTexture(L"asteroid.png");

	
	player.SetDimensions(128.0f, 128.0f);
	platform.SetDimensions(640.0f, 64.0f);
	platform.SetColor(1.0f, 0.0f, 0.0f);
	player.SetColor(0.0f, 1.0f, 0.0f);

	bank.SetTexture(L"Bank.png");
	asteroid.SetTexture(L"asteroid.png");
	radians = 0.0f;

	GetCamera()->AttachCameraToObject(&player);
	GetCamera()->AttachElementToCamera(&asteroid);

}

void GameScreen::Unload()
{
}

void GameScreen::Update(double delta)
{
	radians += 1.0f*delta;

	position = position + EVector(10.0* delta, 10.0* delta) ;
	player.SetPosition(position);
	player.SetOrigin(0.5f, 0.5f);
	player.SetRotation(radians);
	asteroid.SetOrigin(0.5f, 0.5f);
	asteroid.SetRotation(radians);
}

void GameScreen::Render()
{
	player.Render();
	asteroid.Render();
	platform.Render();
	bank.Render();
}

void GameScreen::Input()
{
}

void GameScreen::Shutdown()
{
}

ScreenID GameScreen::GetID()
{
	return SCEEN_GAME;
}
