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

LPPOINT EMouse::GetCursor()
{
	GetCursorPos(&m_cursor);
	
	//HWND hwnd = FindWindow(NULL, "win32app");
	ScreenToClient(EksisEngine::GetInstance()->GetWindow()->GetClientHandle(), &m_cursor);
	m_cursor.y = m_cursor.y*-1 + EksisEngine::GetInstance()->GetWindow()->GetClientHeight();

	return &m_cursor;
}
