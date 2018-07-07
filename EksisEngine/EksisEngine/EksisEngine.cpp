#include "EksisEngine.h"
#include "EWindow.h"
#include "ESquare.h"
#include "ESprite.h"

EksisEngine* EksisEngine::instance = nullptr;

EksisEngine * EksisEngine::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new EksisEngine;
		return instance;
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
		Load(L"Bank.png");
		Load(L"asteroid.png");
		ESquare test;
		ESquare test3;
		ESprite test2;
		ESprite test4(L"asteroid.png");
		test3.SetColor(1.0f, 0.0f, 0.0f);
		test2.SetTexture(L"Bank.png");
		float x, y;
		x = y = 0.0f;
		float radians = 0.0f;
		MSG msg;
		bool done = false;

		while (!done)
		{
			m_input->PollInput();

			if (m_input->GetState(EKeyCode::A) == KEY_DOWN)
			{
				m_x += 1;
			}
			if (m_input->GetState(EKeyCode::D) == KEY_DOWN)
			{
				m_x -= 1;
			}
			if (m_input->GetState(EKeyCode::S) == KEY_DOWN)
			{
				m_y += 1;
			}
			if (m_input->GetState(EKeyCode::W) == KEY_DOWN)
			{
				m_y -= 1;
			}

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
				radians += 0.01f;
				test.SetOrigin(0.5f, 0.5f);
				test.SetPosition(640,360);
				test.SetRotation(radians);
				test.SetScale(3.0f, 0.5f);
				test4.SetPosition(640, 360);
				test4.SetOrigin(0.5f, 0.5f);
				test4.SetRotation(radians);
				m_D3DHelper->BeginRender(0.0f, 0.0f, 0.0f);

				EVector mousePosition = EVector(m_input->GetMouse()->GetCursor()->x, m_input->GetMouse()->GetCursor()->y);
				EVector squarePosition = EVector(m_x, m_y);

				test.SetPosition(mousePosition);
				test.SetOrigin(0, 1);

				test.Render();
		/*		test.Render();
				test3.Render();*/
				test4.Render();
				test2.Render();
				m_D3DHelper->EndRender();
				Sleep(16);
			}

		}
		EksisEngine::GetInstance()->Shutdown();
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
	if (!m_shader->Initialize(m_window->GetClientHandle(), L"color.vs", L"color.ps"))
	{
		MessageBox(m_window->GetClientHandle(), L"Shader Init", L"failed to initialize", MB_OK);
		return false;
	}

	m_input = new EInput();


	m_textureManager = new ETextureManager();
	return true;
}

void EksisEngine::Shutdown()
{
	m_textureManager->Shutdown();
	m_input->Shutdown();
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

float GetClientHeight()
{
	return EksisEngine::GetInstance()->GetWindow()->GetClientHeight();
}

float GetClientWidth()
{
	return EksisEngine::GetInstance()->GetWindow()->GetClientWidth();
}

void Load(const wchar_t * imageFile)
{
	EksisEngine::GetInstance()->GetTextureManager()->Load(imageFile);
}
void Unload(const wchar_t * imageFile)
{
	EksisEngine::GetInstance()->GetTextureManager()->Unload(imageFile);
}
