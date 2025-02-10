#pragma once
#include <memory>
#include "Transform.h"
#include "CppBehaviour.h"
#include <vector>

namespace dae
{
	class Texture2D;

	// todo: this should become final.
	class GameObject final
	{
	public:
		virtual void Update(float deltaTime);
		virtual void Render() const;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		void AddComponent(std::unique_ptr<CppBehaviour> component);

		template <typename T>
		CppBehaviour* GetComponent()
		{
			for (const auto& component : m_OwnedComponents)
			{
				if (auto* castedComponent = dynamic_cast<T*>(component.get()))
				{
					return castedComponent;
				}
			}

			return nullptr;
		}


		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		std::vector<std::unique_ptr<CppBehaviour>> m_OwnedComponents{};
		Transform m_transform{};
		// todo: mmm, every gameobject has a texture? Is that correct?
		std::shared_ptr<Texture2D> m_texture{};
	};
}
