#include "ESprite.h"
#include "EksisEngine.h"

ESprite::ESprite() : 
	m_texture(nullptr),
	m_mesh(nullptr)
{

}

ESprite::ESprite(const wchar_t * imageFile)
{
	m_texture = EksisEngine::GetInstance()->GetTextureManager()->GetTexture(imageFile);

	m_mesh = new EMesh();
	m_mesh->Initialize((float)m_texture->GetWidth(), (float)m_texture->GetHeight());

	__super::SetDimensions((float)m_texture->GetWidth(), (float)m_texture->GetHeight());
}

ESprite::~ESprite()
{
	if (m_mesh)
	{
		delete m_mesh;
		m_mesh = nullptr;
	}
	m_texture = nullptr;
}

bool ESprite::SetTexture(const wchar_t * imageFile)
{
	if (m_texture)
	{
		delete m_texture;
		delete m_mesh;
	}
	m_texture = EksisEngine::GetInstance()->GetTextureManager()->GetTexture(imageFile);

	m_mesh = new EMesh();
	m_mesh->Initialize((float)m_texture->GetWidth(), (float)m_texture->GetHeight());
	
	__super::SetDimensions((float)m_texture->GetWidth(), (float)m_texture->GetHeight());
	
	return true;
}

void ESprite::Shutdown()
{
}

void ESprite::Render()
{
	m_mesh->Render();
	EksisEngine::GetInstance()->GetShader()->SetModel(GetMatrix());
	EksisEngine::GetInstance()->GetShader()->SetView(GetCamera()->GetMatrix());
	EksisEngine::GetInstance()->GetShader()->SetOrtho(EksisEngine::GetInstance()->GetWindow()->GetOrthoMatrix());
	EksisEngine::GetInstance()->GetShader()->Render(m_mesh->GetIndexCount(),m_texture->GetTexture());
}
