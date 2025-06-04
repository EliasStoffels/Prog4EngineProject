#include <stdexcept>
#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "GameObject.h"

dae::TextComponent::TextComponent(std::shared_ptr<Font> font, const std::string text, glm::vec3 offset)
	: m_needsUpdate(true), m_textTexture(nullptr), m_RenderOffset{offset}
{ 
	SetFont(font);
	SetText(text);
}

dae::TextComponent::TextComponent()
	: m_needsUpdate(true), m_textTexture(nullptr)
{
}

void dae::TextComponent::Update(float)
{
	if (m_needsUpdate)
	{
		const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), m_Color);
		if (surf == nullptr) 
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr) 
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_textTexture = std::make_shared<Texture2D>(texture);
		m_needsUpdate = false;
	}
}

void dae::TextComponent::Render() const
{
	if (m_textTexture != nullptr)
	{
		const auto& pos = m_OwningGameObject->GetTransform()->GetWorldPosition() + m_RenderOffset;
		Renderer::GetInstance().RenderTexture(*m_textTexture, pos.x, pos.y);
	}
}

void dae::TextComponent::SetFont(std::shared_ptr<Font> font)
{
	m_font = std::move(font);
}

void dae::TextComponent::SetRenderOfSet(const glm::vec3& ofsett)
{
	m_RenderOffset = ofsett;
}

void dae::TextComponent::SetColor(const SDL_Color& color)
{
	m_Color = color;
}

void dae::TextComponent::SetColor(int r, int g, int b, int a)
{
	m_Color = SDL_Color{ static_cast<unsigned char>(r),static_cast<unsigned char>(g),static_cast<unsigned char>(b),static_cast<unsigned char>(a) };
}

// This implementation uses the "dirty flag" pattern
void dae::TextComponent::SetText(const std::string& text)
{
	if (m_text == text)
		return;
	m_text = text;
	m_needsUpdate = true;
}


