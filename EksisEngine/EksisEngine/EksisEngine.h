#pragma once
#include "ED3DHelper.h"
#include "EShader.h"
#include "EWindow.h"
#include "ETextureManager.h"
#include "EEngineTimer.h"
#include "ECamera.h"
#include "EPhysicsEngine.h"

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
	EPhysicsEngine* GetPhysicsEngine();

private:
	EksisEngine();
	~EksisEngine();
	bool Initialize();
private:
	static EksisEngine * instance;
	EWindow * m_window;
	ED3DHelper* m_D3DHelper;
	EShader * m_shader;
	ETextureManager* m_textureManager;
	EEngineTimer m_engineTimer;
	ECamera* m_camera;
	EPhysicsEngine* m_physicsEngine;
};

int GetClientHeight();
int GetClientWidth();
void LoadTexture(const wchar_t* imageFile);
void UnloadTexture(const wchar_t* imageFile);
ECamera* GetCamera();
EPhysicsEngine* GetPhysicsEngine();