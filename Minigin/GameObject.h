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
		void Start();

		void Update(float deltaTime);
		void Render() const;

		//void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);
		Transform GetTransform();

		void AddComponent(std::unique_ptr<CppBehaviour> component);

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		// template functions
		template <typename T>
		CppBehaviour* GetComponent(int index = 0)
		{
			int currentIndex = 0;
			for (const auto& component : m_OwnedComponents)
			{
				if (auto* castedComponent = dynamic_cast<T*>(component.get()))
				{
					if (currentIndex == index)
						return castedComponent;
					++currentIndex;
				}
			}

			return nullptr;
		}

		template <typename T>
		void RemoveComponent(int index = 0)
		{
			int currentIndex = 0;
			for (const auto& component : m_OwnedComponents)
			{
				if (auto* castedComponent = dynamic_cast<T*>(component.get()))
				{
					if (currentIndex == index)
						castedComponent->pendingRemove = true;
					++currentIndex;
				}
			}
		}

		template <typename T>
		void RemoveAllComponentOfType()
		{
			for (const auto& component : m_OwnedComponents)
			{
				if (auto* castedComponent = dynamic_cast<T*>(component.get()))
				{
					castedComponent->pendingRemove = true;
				}
			}
		}

		template <typename T>
		bool HasComponent()
		{
			for (const auto& component : m_OwnedComponents)
			{
				if (auto* castedComponent = dynamic_cast<T*>(component.get()))
				{
					return true;
				}
			}

			return false;
		}


	private:
		std::vector<std::unique_ptr<CppBehaviour>> m_OwnedComponents{};
		Transform m_transform{};
		// todo: mmm, every gameobject has a texture? Is that correct?
		//std::shared_ptr<Texture2D> m_texture{};
	};
}
