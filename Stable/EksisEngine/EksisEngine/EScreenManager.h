#pragma once
#include "Screen.h"
#include <map>
#include <stack>

class EScreenManager
{
public:
	static EScreenManager *GetInstance();
	EScreenManager();
	void Shutdown();
	void AddScreen(Screen *screen);
	void SetScreen(ScreenID id);
	void PushScreen(ScreenID id);
	void PopScreen();
	Screen *GetScreen(ScreenID id);
	ScreenID GetCurrentScreenID();
	Screen *GetCurrentScreen();
private:
	static EScreenManager *instance;
	std::map<ScreenID, Screen*> m_screenMap;
	std::stack<Screen*> m_currentScreen;
	ScreenID m_currentScreenID;
};