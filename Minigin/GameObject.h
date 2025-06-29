#pragma once
#include <memory>
#include "Transform.h"
#include "CppBehaviour.h"
#include <vector>
#include "BaseObserver.h"

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

		void SetWorldPosition(float x, float y, float z = 0.f);
		void SetWorldPosition(glm::vec3 pos);
		void SetLocalPosition(float x, float y, float z = 0.f);
		void SetLocalPosition(glm::vec3 pos);
		glm::vec3 GetWorldPosition();
		glm::vec3 GetLocalPosition();

		void Destroy();

		GameObject* GetParent();
		void SetParent(GameObject* parent, bool keepWorldPosition);
		bool IsChild(GameObject* otherObject);
		std::vector<GameObject*>* GetChildren();

		void AddObserver(Observer* observer);
		void RemoveObserver(Observer* observer);
		void NotifyObservers(const Event& event);

		Transform* GetTransform();

		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		// template functions
		template <typename T, typename... Args>
		T* AddComponent(Args&&... args)
		{
			if (std::is_base_of<CppBehaviour, T>::value)
			{
				std::unique_ptr<T> component(new T(this,std::forward<Args>(args)...));
				m_OwnedComponents.emplace_back(std::move(component));
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
	protected:
			
	private:
		std::vector<std::unique_ptr<CppBehaviour>> m_OwnedComponents{};
		std::vector<GameObject*> m_childObjects{};
		std::vector<Observer*> m_observers{};
		GameObject* m_parent = nullptr;
		Transform m_transform{};
	};
}
