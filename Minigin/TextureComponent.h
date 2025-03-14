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
		friend class GameObject;
	public:
		void Render() const override;

		void SetTexture(const std::string& filename);
		
		virtual ~TextureComponent() = default;
		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;
	private:
		TextureComponent();
		std::shared_ptr<Texture2D> m_texture = nullptr;
	};
}
