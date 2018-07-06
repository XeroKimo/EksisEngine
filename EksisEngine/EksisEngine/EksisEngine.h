#pragma once

#include "ED3DHelper.h"
#include "EShader.h"
#include "EWindow.h"
#include "EInput.h"

#include "EKeyCodes.h"

class EksisEngine
{
public:
	static EksisEngine * GetInstance();

	bool Run();
	void Shutdown();
	ED3DHelper* GetD3DHelper();
	EShader* GetShader();
	EWindow* GetWindow();

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
