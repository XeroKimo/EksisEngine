#pragma once

#include "ED3DHelper.h"
#include "EShader.h"
#include "EWindow.h
#include "EInput.h"

#include "EKeyCodes.h"
#include "ETextureManager.h"
#include "EEngineTimer.h"
#include "ECamera.h"

class EksisEngine
{
public:
	static EksisEngine * GetInstance();

	bool Run();
	void Shutdown();
	ED3DHelper* GetD3DHelper();
	EShader* GetShader();
	EWindow* GetWindow();
	ETextureManager* GetTextureManager();
	ECamera* GetCamera();

private:
	EksisEngine();
	~EksisEngine();
	bool Initialize();
private:
	static EksisEngine * instance;
	EWindow * m_window;
	ED3DHelper* m_D3DHelper;
	EShader * m_shader;
	
	EInput* m_input;

	// The stuff below is for testing.
	float m_x = 0;
	float m_y = 0;
};
	ETextureManager* m_textureManager;
	EEngineTimer m_engineTimer;
	ECamera* m_camera;
};

int GetClientHeight();
int GetClientWidth();
void LoadTexture(const wchar_t* imageFile);
void UnloadTexture(const wchar_t* imageFile);
ECamera* GetCamera();
