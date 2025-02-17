#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include <iostream>


dae::GameObject::~GameObject() = default;

void dae::GameObject::Start()
{
	for (const auto& component : m_OwnedComponents)
	{
		component->Start();
	}
}

void dae::GameObject::Update(float deltaTime)
{
	for (const auto& component : m_OwnedComponents)
	{
		component->Update(deltaTime);
	}

	auto removeIter = std::remove_if(m_OwnedComponents.begin(), m_OwnedComponents.end(),
		[](const std::unique_ptr<CppBehaviour>& component) { return component->pendingRemove; });
	m_OwnedComponents.erase(removeIter, m_OwnedComponents.end());
}

void dae::GameObject::FixedUpdate(float fixedTime)
{
	for (const auto& component : m_OwnedComponents)
	{
		component->FixedUpdate(fixedTime);
	}
}

void dae::GameObject::LateUpdate(float deltaTime)
{
	for (const auto& component : m_OwnedComponents)
	{
		component->LateUpdate(deltaTime);
	}
}

void dae::GameObject::Render() const
{
	for (const auto& component : m_OwnedComponents)
	{
		component->Render();
	}
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}

dae::Transform dae::GameObject::GetTransform()
{
	return m_transform;
}
