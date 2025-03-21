#pragma once
#include <string>
#include <memory>
#include "CppBehaviour.h"
#include "Transform.h"

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
		void SetRenderOfSet();
		
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
		glm::vec3 RenderOffset{};
	};
}
