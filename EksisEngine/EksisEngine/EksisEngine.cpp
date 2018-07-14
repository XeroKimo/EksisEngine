#include "EksisEngine.h"
#include "ESquare.h"
#include "ESprite.h"
#include "EScreenManager.h"
#include "ScreenInit.h"

EksisEngine* EksisEngine::instance = nullptr;

EksisEngine * EksisEngine::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new EksisEngine;
	}
	return instance;
}

EksisEngine::EksisEngine():
	m_window(nullptr),
	m_shader(nullptr)
{
}

EksisEngine::~EksisEngine()
{
}


bool EksisEngine::Run()
{
	if (!Initialize())
	{
		return false;
	}
	else
	{
		
		MSG msg;
		bool done = false;
		while (!done)
		{
			if (PeekMessage(&msg, NULL, NULL, NULL,PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			if (msg.message == WM_QUIT)
			{
				done = true;
			}
			else
			{
				m_input->PollInput();
				m_engineTimer.Tick();
				m_camera->Update(m_engineTimer.GetDelta());
				m_physicsEngine->Update(m_engineTimer.GetDelta());
				EScreenManager::GetInstance()->GetCurrentScreen()->Update(m_engineTimer.GetDelta());
				m_D3DHelper->BeginRender(0.0f, 0.0f, 0.0f);
				m_camera->Render();
				EScreenManager::GetInstance()->GetCurrentScreen()->Render();
				m_D3DHelper->EndRender();
				EScreenManager::GetInstance()->GetCurrentScreen()->Input(m_input);
			}

		}
		return (int)msg.wParam;
	}
}

bool EksisEngine::Initialize()
{
	m_window = new EWindow();
	if (m_window->Initialize(L"win32 app", 1280, 720))
	{
		MessageBox(m_window->GetClientHandle(), L"Window Init", L"failed to initialize", MB_OK);
		return false;
	}

	m_D3DHelper = new ED3DHelper();
	if (!m_D3DHelper->Initialize(m_window->GetClientWidth(), m_window->GetClientHeight(), m_window->GetClientHandle()))
	{
		MessageBox(m_window->GetClientHandle(), L"D3D Init", L"failed to initialize", MB_OK);
		return false;
	}

	m_shader = new EShader();
	if (!m_shader->Initialize(m_window->GetClientHandle(), L"texture.vs", L"texture.ps"))
	{
		MessageBox(m_window->GetClientHandle(), L"Shader Init", L"failed to initialize", MB_OK);
		return false;
	}
	m_textureManager = new ETextureManager();
	m_textureManager->Initialize();
	m_camera = new ECamera();
	m_input = new EInput();
	m_physicsEngine = new EPhysicsEngine();
	ScreenInit screenInit;
	screenInit.Initialize();


	return true;
}

void EksisEngine::Shutdown()
{
	m_input->Shutdown();
	m_physicsEngine->Shutdown();
	m_textureManager->Shutdown();
	m_shader->Shutdown();
	m_D3DHelper->Shutdown();
	m_window->Shutdown();
}

ED3DHelper * EksisEngine::GetD3DHelper()
{
	return m_D3DHelper;
}

EShader * EksisEngine::GetShader()
{
	return m_shader;
}

EWindow * EksisEngine::GetWindow()
{
	return m_window;
}

ETextureManager * EksisEngine::GetTextureManager()
{
	return m_textureManager;
}

ECamera * EksisEngine::GetCamera()
{
	return m_camera;
}

EPhysicsEngine * EksisEngine::GetPhysicsEngine()
{
	return m_physicsEngine;
}

EInput * EksisEngine::GetInput()
{
	return m_input;
}

int GetClientHeight()
{
	return EksisEngine::GetInstance()->GetWindow()->GetClientHeight();
}

int GetClientWidth()
{
	return EksisEngine::GetInstance()->GetWindow()->GetClientWidth();
}

void LoadTexture(const wchar_t * imageFile)
{
	EksisEngine::GetInstance()->GetTextureManager()->Load(imageFile);
}
void UnloadTexture(const wchar_t * imageFile)
{
	EksisEngine::GetInstance()->GetTextureManager()->Unload(imageFile);
}

ECamera * GetCamera()
{
	return EksisEngine::GetInstance()->GetCamera();
}

EPhysicsEngine * GetPhysicsEngine()
{
	return EksisEngine::GetInstance()->GetPhysicsEngine();
}
bool IsKeyInactive(EKeyCode key)
{
	if (EksisEngine::GetInstance()->GetInput()->GetState(key) == KEY_INACTIVE)
	{
		return true;
	}
	return false;
}

bool IsKeyUp(EKeyCode key)
{
	if (EksisEngine::GetInstance()->GetInput()->GetState(key) == KEY_UP)
	{
		return true;
	}
	return false;
}

bool IsKeyDown(EKeyCode key)
{
	if (EksisEngine::GetInstance()->GetInput()->GetState(key) == KEY_DOWN)
	{
		return true;
	}
	return false;
}

bool IsKeyHeld(EKeyCode key)
{
	if (EksisEngine::GetInstance()->GetInput()->GetState(key) == KEY_HELD)
	{
		return true;
	}
	return false;
}
