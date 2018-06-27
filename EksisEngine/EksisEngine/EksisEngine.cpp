#include "EksisEngine.h"
#include "EWindow.h"
#include "ESquare.h"

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
		ESquare test;
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
				m_D3DHelper->BeginRender(0.0f, 0.0f, 0.0f);
				test.Render();
				m_D3DHelper->EndRender();
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
	return true;
}

void EksisEngine::Shutdown()
{
	if (m_window)
	{
		m_window->Shutdown();
		delete m_window;
		m_window = nullptr;
	}
	if (m_D3DHelper)
	{
		m_D3DHelper->Shutdown();
		delete m_D3DHelper;
		m_D3DHelper = nullptr;
	}
	if (m_shader)
	{
		m_shader->Shutdown();
		delete m_shader;
		m_shader = nullptr;
	}
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
