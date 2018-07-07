#include "ScreenInit.h"
#include "EScreenManager.h"
#include "GameScreen.h"

ScreenInit::ScreenInit()
{
}

void ScreenInit::Initialize()
{
	GameScreen *game = new GameScreen();
	EScreenManager::GetInstance()->AddScreen(game);
	EScreenManager::GetInstance()->PushScreen(game->GetID());
}
