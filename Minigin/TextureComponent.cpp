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
	if (!m_Render)
		return;

	const auto& pos = m_OwningGameObject->GetWorldPosition();
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

void dae::TextureComponent::SetSourceRect(int x, int y, int width, int height)
{
	if (width != -1)
		SetSourceRect(SDL_Rect{ x,y,width,height });
	else
		SetSourceRect(SDL_Rect{x,y,m_SourceRect.w,m_SourceRect.h});
}

void dae::TextureComponent::SetSourceRect(const SDL_Rect& rect)
{
	m_SourceRect = rect;
}

void dae::TextureComponent::IsActive(bool isActive)
{
	m_Render = isActive;
}


