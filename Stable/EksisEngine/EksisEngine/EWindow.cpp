#include "EWindow.h"

EWindow::EWindow()
{
}

EWindow::~EWindow()
{

}

int EWindow::Initialize(const wchar_t *name, int width, int height)
{
	m_hInstance = GetModuleHandle(NULL);
	m_windowName = *name;
	m_width = width;
	m_height = height;
	m_orthoMatrix = EMatrix::Ortho(0, width, 0, height);


	WNDCLASSEX wcex = {};

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInstance;
	wcex.hIcon = LoadIcon(m_hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hIconSm = wcex.hIcon;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = name;


	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL, L"Call to RegisterClassEx failed!", L"Win32 Guided Tour", NULL);
		return 1;
	}

	// The parameters to CreateWindow explained:  
	// szWindowClass: the name of the application  
	// szTitle: the text that appears in the title bar  
	// WS_OVERLAPPEDWINDOW: the type of window to create  
	// CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)  
	// 500, 100: initial size (width, length)  
	// NULL: the parent of this window  
	// NULL: this application does not have a menu bar  
	// hInstance: the first parameter from WinMain  
	// NULL: not used in this application  
	int ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	int ScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	m_hWnd = CreateWindowEx(WS_EX_APPWINDOW, name, name, WS_OVERLAPPEDWINDOW, (ScreenWidth - width) /2,(ScreenHeight - height) /2, width, height, NULL, NULL, m_hInstance, NULL);
	if (!m_hWnd)
	{
		MessageBox(NULL, L"Error Making window", L"Win32 Guided Tour", NULL);
		return 1;
	}
	ShowWindow(m_hWnd, SW_SHOW);
	SetForegroundWindow(m_hWnd);
	SetFocus(m_hWnd);

	return 0;
}

void EWindow::Shutdown()
{
	DestroyWindow(m_hWnd);
	UnregisterClass(&m_windowName, m_hInstance);
}

LRESULT CALLBACK EWindow::WndProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(window, message, wParam, lParam);
		break;

	}
	return 0;
}

int EWindow::GetClientWidth()
{
	return m_width;
}

int EWindow::GetClientHeight()
{
	return m_height;
}

HWND EWindow::GetClientHandle()
{
	return m_hWnd;
}

EMatrix EWindow::GetOrthoMatrix()
{
	return m_orthoMatrix;
}
