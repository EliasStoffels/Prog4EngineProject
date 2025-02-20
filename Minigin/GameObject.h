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
		void FixedUpdate(float fixedTime);
		void LateUpdate(float deltaTime);
		void Render() const;

		//void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);
		Transform GetTransform();

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		// template functions
		template <typename T>
		CppBehaviour* AddComponent()
		{
			if (std::is_base_of<CppBehaviour, T>::value)
			{
				std::unique_ptr<T> component(new T());
				component->SetOwningGameObject(*this);
				m_OwnedComponents.push_back(std::move(component));
				return m_OwnedComponents[m_OwnedComponents.size() - 1].get();
			}
		}

		template <typename T>
		T* GetComponent()
		{
			int currentIndex = 0;
			for (const auto& component : m_OwnedComponents)
			{
				if (auto* castedComponent = dynamic_cast<T*>(component.get()))
				{
					return castedComponent;
				}
			}

			return nullptr;
		}

		template <typename T>
		void RemoveComponent(T* component = nullptr)
		{
			if (!std::is_base_of<CppBehaviour, T>::value)
				return;

			if (T)
			{
				component->pendingRemoval = true;
				return;
			}

			for (const auto& component : m_OwnedComponents)
			{
				if (auto* castedComponent = dynamic_cast<T*>(component.get()))
				{
					castedComponent->pendingRemove = true;
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

		bool pendingRemove = false;
	private:
		std::vector<std::unique_ptr<CppBehaviour>> m_OwnedComponents{};
		Transform m_transform{};
	};
}
