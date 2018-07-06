
#include <Windows.h>
#include "EksisEngine.h"


#if defined(_DEBUG) || defined(DEBUG)
int main()
#else
int CALLBACK WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,  LPSTR lpCmdLine,  int nCmdShow)
#endif
{
	EksisEngine::GetInstance()->Run();
	EksisEngine::GetInstance()->Shutdown();
	system("Pause");
	return 0;
}
