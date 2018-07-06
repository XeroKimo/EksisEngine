#pragma once

#include <windows.h>
#include <map>
#include <iostream>

#include "EKeyCodes.h"
#include "EController.h"

class EMouse: public EController
{
private:
	tagPOINT m_cursor;
	float m_cursorX;
	float m_cursorY;

public:
	EMouse();

	LPPOINT GetCursor();
};
