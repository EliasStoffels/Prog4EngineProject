#pragma once
#include "CppBehaviour.h"
#include <string>
#include <memory>
#include "Transform.h"

namespace dae
{
	class Font;
	class Texture2D;
	class TextureComponent : public CppBehaviour
	{
	public:
		void Render() const override;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		TextureComponent(const std::string& filename);
		virtual ~TextureComponent() = default;
		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;
	private:
		Transform m_transform{};
		std::shared_ptr<Texture2D> m_texture;
	};
}
