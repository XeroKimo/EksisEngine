
#include <Windows.h>
#include <strsafe.h>
#include "EksisEngine.h"


int CALLBACK WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,  LPSTR lpCmdLine,  int nCmdShow)
{
	EksisEngine::GetInstance()->Run();
	EksisEngine::GetInstance()->Shutdown();
}