#include "EMouse.h"
#include "EksisEngine.h"

EMouse::EMouse()
{
	m_keyMap.insert({ EKeyCode::MOUSE1, false });
	m_keyMap.insert({ EKeyCode::MOUSE2, false });
	m_keyMap.insert({ EKeyCode::MOUSE3, false });
	m_keyMap.insert({ EKeyCode::MOUSE4, false });
	m_keyMap.insert({ EKeyCode::MOUSE5, false });
}

#include <cmath>


LPPOINT EMouse::GetCursor()
{
	//RECT gameWindow;
	//GetWindowRect(EksisEngine::GetInstance()->GetWindow()->GetClientHandle(), &gameWindow);

	RECT virtualGameWindow;
	GetClientRect(EksisEngine::GetInstance()->GetWindow()->GetClientHandle(), &virtualGameWindow);

	//RECT desktop;
	//GetWindowRect(GetDesktopWindow(), &desktop);

	GetCursorPos(&m_cursor);
	
	//HWND hwnd = FindWindow(NULL, L"win32app");
	ScreenToClient(EksisEngine::GetInstance()->GetWindow()->GetClientHandle(), &m_cursor);
	
	m_cursor.y = m_cursor.y*-1 + virtualGameWindow.bottom;

	return &m_cursor;
}
