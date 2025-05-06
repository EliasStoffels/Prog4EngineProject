#include "TextureComponent.h"
#include "Texture2D.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"

dae::TextureComponent::TextureComponent()
{
}

void dae::TextureComponent::Render() const
{
	const auto& pos = m_OwningGameObject->GetTransform()->GetWorldPosition();
	if(m_Width == FLT_MAX)
		Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
	else if(m_SourceRect.x == INT_MAX)
		Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y, m_Width, m_Height);
	else
		Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y, m_Width, m_Height, m_SourceRect);
}

void dae::TextureComponent::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}


