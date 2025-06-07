#pragma once
#include "CppBehaviour.h"
#include <string>
#include <memory>
#include "Transform.h"
#include "SDL_rect.h"

namespace dae
{
	class Font;
	class Texture2D;
	class TextureComponent : public CppBehaviour
	{
		friend class GameObject;
	public:
		void Render() const override;

		void SetTexture(const std::string& filename);
		void SetWidthAndHeight(float width, float height) { m_Width = width; m_Height = height; }
		void SetSourceRect(int x, int y, int widht = -1, int height = -1);
		void SetSourceRect(const SDL_Rect& rect);
		void SetRepeats(int repeats);
		void SetRepeatOfsett(const glm::vec3& ofset);
		void SetRenderOfsett(const glm::vec3& ofset);
		void IsActive(bool isActive);

		SDL_Rect GetSourceRect() { return m_SourceRect; }

		virtual ~TextureComponent() = default;
		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;
	private:
		TextureComponent(GameObject* owner);
		std::shared_ptr<Texture2D> m_texture = nullptr;
		float m_Width = FLT_MAX;
		float m_Height = FLT_MAX;
		SDL_Rect m_SourceRect{ INT_MAX,INT_MAX,INT_MAX,INT_MAX };
		bool m_Render = true;
		int m_Repeats = 1;
		glm::vec3 m_RepeatOfsett{};
		glm::vec3 m_RenderOfsett{};
	};
}
