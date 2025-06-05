#pragma once
#include <string>
#include <memory>
#include "CppBehaviour.h"
#include "Transform.h"
#include <SDL_ttf.h>

namespace dae
{
	class Font;
	class Texture2D;
	class TextComponent : public CppBehaviour
	{
		friend class GameObject;

	public:
		void Update(float deltaTime) override;
		void Render() const override;

		void SetText(const std::string& text);
		void SetFont(std::shared_ptr<Font> font);
		void SetRenderOfSet(const glm::vec3& ofsett);
		void SetColor(const SDL_Color& color);
		void SetColor(int r, int g, int b, int a = 255);

		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;
	private:
		TextComponent(std::shared_ptr<Font> font, const std::string text = "Default Text", glm::vec3 offset = glm::vec3{});
		TextComponent();
		bool m_needsUpdate;
		std::string m_text;
		std::shared_ptr<Font> m_font = nullptr;
		std::shared_ptr<Texture2D> m_textTexture = nullptr;
		glm::vec3 m_RenderOffset{};
		SDL_Color m_Color = { 255,255,255,255 };
	};
}
