#include "GameScreen.h"

GameScreen::GameScreen()
{

}

GameScreen::~GameScreen()
{
}

void GameScreen::Load()
{

	m_player1.SetPosition(EVector(0.0f,300.0f));
	//m_player1.SetHitboxPosition(m_player1.GetSquare().GetPosition());
	m_player1.SetMass(1.0f);

	m_platform1.GetSquare().SetDimensions(EVector(640.0f, 128.0f));
	m_platform1.SetHitbox(m_platform1.GetSquare().GetDimension());

	m_platform2.GetSquare().SetDimensions(128.0f, 128.0f);
	m_platform2.SetHitbox(m_platform2.GetSquare().GetDimension());
	m_platform2.GetSquare().SetPosition(512.0f,128.0f);

	//m_box1.SetPosition(EVector(0.0f,128.0f));
	m_box1.SetPosition(EVector(300.0f, 500.0f));
	GetCamera()->AttachCameraToObject(&m_player1.GetSquare());
}

void GameScreen::Unload()
{
}

void GameScreen::Update(double delta)
{
	m_player1.Update(delta);
	m_platform1.Update(delta);
	m_platform2.Update(delta);
	m_box1.Update(delta);
}

void GameScreen::Render()
{
	m_player1.Render();
	m_platform1.Render();
	m_platform2.Render();
	m_box1.Render();
}

void GameScreen::Input(EInput* input)
{
	m_player1.Input(input);
}

void GameScreen::Shutdown()
{
}

ScreenID GameScreen::GetID()
{
	return SCEEN_GAME;
}
