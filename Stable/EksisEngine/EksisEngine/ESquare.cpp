#include "ESquare.h"
#include "EMesh.h"
#include "EksisEngine.h"

ESquare::ESquare(float width, float height) :
	ERenderable(width,height),
	m_display(true)
{
	m_red = m_green = m_alpha = m_blue = 1.0f;
	m_mesh = new EMesh();
	m_mesh->Initialize(width, height);
}

ESquare::~ESquare()
{
	if (m_mesh)
	{
		delete m_mesh;
		m_mesh = nullptr;
	}
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
	EksisEngine::GetInstance()->GetShader()->SetView(GetCamera()->GetMatrix());
	EksisEngine::GetInstance()->GetShader()->SetOrtho(EksisEngine::GetInstance()->GetWindow()->GetOrthoMatrix());
	EksisEngine::GetInstance()->GetShader()->Render(m_mesh->GetIndexCount(),EksisEngine::GetInstance()->GetTextureManager()->BlankTexture());
}

void ESquare::SetColor(float r, float g, float b, float a)
{
	m_red = r;
	m_green = g;
	m_blue = b;
	m_alpha = a;
	m_mesh->SetColor(r, g, b, a);
}

void ESquare::SetDimensions(float width, float height)
{
	delete m_mesh;
	m_mesh = new EMesh();
	m_mesh->Initialize(width, height);
	m_mesh->SetColor(m_red, m_green, m_blue, m_alpha);
	__super::SetDimensions(width, height);
}

void ESquare::SetDimensions(EVector dimensions)
{
	delete m_mesh;
	m_mesh = new EMesh();
	m_mesh->Initialize(dimensions.x,dimensions.y);
	m_mesh->SetColor(m_red, m_green, m_blue, m_alpha);
	__super::SetDimensions(dimensions);
}



