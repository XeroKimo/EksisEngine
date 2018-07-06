#pragma once

#include "EMatrix.h"
#include <Windows.h>
#include <windowsx.h>

class EWindow
{
public:
	EWindow();
	~EWindow();

	int Initialize(const wchar_t *name, int width, int height);
	void Shutdown();

	static LRESULT CALLBACK WndProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam);

	int GetClientWidth();
	int GetClientHeight();
	HWND GetClientHandle();
	HINSTANCE GetClientInstance();

	EMatrix GetOrthoMatrix();

private:
	MSG m_msg;
	HWND m_hWnd;
	HINSTANCE m_hInstance;
	wchar_t m_windowName;
	int m_width;
	int m_height;
	EMatrix m_orthoMatrix;
};