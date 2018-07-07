#include "EInput.h"

EInput::EInput()
{
	m_keyboard = EKeyboard();
	m_mouse = EMouse();

	m_context = 0;
}

void EInput::Shutdown()
{
	if (&m_keyboard)
	{
		delete &m_keyboard;
	}
	if (&m_mouse)
	{
		delete &m_mouse;
	}
}

EKeyboard* EInput::GetKeyboard()
{
	return &m_keyboard;
}

EMouse* EInput::GetMouse()
{
	return &m_mouse;
}

void EInput::PollInput()
{
	m_keyboard.PollInput();
	m_mouse.PollInput();
}

int EInput::GetState(EKeyCode key)
{
	int state;

	if ((state = m_keyboard.GetState(key)) != KEY_ERROR)
	{
		return m_keyboard.GetState(key);
	}
	else if((state = m_mouse.GetState(key)) != KEY_ERROR)
	{
		return m_mouse.GetState(key);
	}
	else
	{
		return KEY_ERROR;
	}
}
