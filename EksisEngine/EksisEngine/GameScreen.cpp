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
	player.SetColor(0.0f, 1.0f, 0.0f);
	platform.SetDimensions(640.0f, 64.0f);
	platform.SetColor(1.0f, 0.0f, 0.0f);

	bank.SetTexture(L"Bank.png");
	asteroid.SetTexture(L"asteroid.png");
	radians = 0.0f;

	m_player1.GetSquare().SetPosition(0.0f, 720.0f);
	m_player1.SetMass(1.0f);
	GetCamera()->AttachCameraToObject(&m_player1.GetSquare());
	GetCamera()->AttachElementToCamera(&asteroid);
	//GetCamera()->DetachElementFromCamera(&asteroid);

}

void GameScreen::Unload()
{
}

void GameScreen::Update(double delta)
{
	radians += 1.0f*delta;

	m_player1.Update(delta);
	//GetCamera()->SetPosition(-200.0f, -200.0f);
	asteroid.SetOrigin(0.5f, 0.5f);
	asteroid.SetRotation(radians);
	player.SetPosition(position);
	player.SetOrigin(0.5f, 0.5f);
	player.SetRotation(radians);
}

void GameScreen::Render()
{
	m_player1.Render();
	player.Render();
	platform.Render();
	bank.Render();
	player.Render();
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
