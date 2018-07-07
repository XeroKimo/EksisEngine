#include "EScreenManager.h"

EScreenManager* EScreenManager::instance = nullptr;
EScreenManager * EScreenManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new EScreenManager();
	}
	return instance;
}

EScreenManager::EScreenManager()
{
}

void EScreenManager::Shutdown()
{
}

void EScreenManager::AddScreen(Screen * screen)
{
	m_screenMap[screen->GetID()] = screen;
}

void EScreenManager::SetScreen(ScreenID id)
{
	m_currentScreenID = id;
}

void EScreenManager::PushScreen(ScreenID id)
{
	if (!m_currentScreen.empty())
	{
		m_currentScreen.top()->Unload();
	}
	m_currentScreen.push(m_screenMap[id]);
	m_currentScreen.top()->Load();
	m_currentScreenID = id;
}

void EScreenManager::PopScreen()
{
	m_currentScreen.top()->Unload();
	m_currentScreen.pop();
	m_currentScreen.top()->Load();
	m_currentScreenID = m_currentScreen.top()->GetID();
}

Screen * EScreenManager::GetScreen(ScreenID id)
{
	return m_screenMap[id];
}

ScreenID EScreenManager::GetCurrentScreenID()
{
	return m_currentScreenID;
}

Screen * EScreenManager::GetCurrentScreen()
{
	return m_currentScreen.top();
}
