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
	const auto& pos = m_OwningGameObject->GetTransform().GetWorldPosition();
	Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
}

void dae::TextureComponent::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}


