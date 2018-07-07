#include "ESquare.h"
#include "EMesh.h"
#include "EksisEngine.h"

#include <iostream>			// remove this later

ESquare::ESquare(float width, float height) :
	ERenderable(width,height),
	m_display(true)
{
	m_mesh = new EMesh();
	m_mesh->Initialize(width, height);
}

ESquare::~ESquare()
{
}

void ESquare::Load()
{
	m_display = true;
}

void ESquare::Unload()
{
	m_display = false;
}

void ESquare::Render()
{
	m_mesh->Render();
	EksisEngine::GetInstance()->GetShader()->SetModel(GetMatrix());
	EksisEngine::GetInstance()->GetShader()->SetView(EMatrix::Identity());
	EksisEngine::GetInstance()->GetShader()->SetOrtho(EksisEngine::GetInstance()->GetWindow()->GetOrthoMatrix());
	EksisEngine::GetInstance()->GetShader()->Render(m_mesh->GetIndexCount());
}



