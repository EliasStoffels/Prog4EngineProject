#pragma once
#include <memory>
#include "Transform.h"
#include "CppBehaviour.h"
#include <vector>

namespace dae
{
	class Texture2D;

	class GameObject final
	{
	public:
		void Start();

		void Update(float deltaTime);
		void FixedUpdate(float fixedTime);
		void LateUpdate(float deltaTime);
		void Render() const;

		void SetLocalPosition(float x, float y);
		void SetLocalPosition(glm::vec3 pos);
		glm::vec3 GetWorldPosition();

		void SetParent(GameObject* parent, bool keepWorldPosition);
		bool IsChild(GameObject* otherObject);
		std::vector<GameObject*>* GetChildren();

		Transform* GetTransform();

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		// template functions
		template <typename T>
		T* AddComponent()
		{
			if (std::is_base_of<CppBehaviour, T>::value)
			{
				std::unique_ptr<T> component(new T());
				component->SetOwningGameObject(*this);
				m_OwnedComponents.push_back(std::move(component));
				return static_cast<T*>(m_OwnedComponents[m_OwnedComponents.size() - 1].get());
			}
		}

		template <typename T>
		T* GetComponent()
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

		template <typename T>
		void RemoveComponent(T* component = nullptr)
		{
			if (!std::is_base_of<CppBehaviour, T>::value)
				return;

			if (component)
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
		std::vector<GameObject*> m_childObjects{};
		GameObject* m_parent = nullptr;
		Transform m_transform{};
	};
}
