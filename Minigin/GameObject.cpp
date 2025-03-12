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

void dae::GameObject::SetLocalPosition(float x, float y)
{
	m_transform.SetLocalPosition(x, y, 0.0f);
}

void dae::GameObject::SetLocalPosition(glm::vec3 pos)
{
	m_transform.SetLocalPosition(pos);
}

glm::vec3 dae::GameObject::GetWorldPosition()
{
	return m_transform.GetWorldPosition();
}

void dae::GameObject::SetParent(GameObject* parent, bool keepWorldPosition)
{
	if (IsChild(parent) || parent == this || m_parent == parent)
		return;
	if (parent == nullptr)
		SetLocalPosition(GetWorldPosition());
	else
	{
		if (keepWorldPosition)
			SetLocalPosition(GetWorldPosition() - parent->GetWorldPosition());
		m_transform.SetPositionDirty();
	}

	if (m_parent)
	{
		m_parent->m_childObjects.erase(std::remove(m_parent->m_childObjects.begin(), m_parent->m_childObjects.end(),this), m_parent->m_childObjects.end());
	}
	m_parent = parent;
	if (m_parent)
	{
		m_parent->m_childObjects.push_back(this);
	}
	m_transform.m_parent = m_parent;
	m_transform.m_childObjects = &m_childObjects;
}

bool dae::GameObject::IsChild(GameObject* otherObject)
{
	for (const auto& child : m_childObjects)
	{
		if (otherObject == child)
			return true;
	}

	return false;
}

std::vector<dae::GameObject*>* dae::GameObject::GetChildren()
{
	return &m_childObjects;
}

dae::Transform* dae::GameObject::GetTransform()
{
	return &m_transform;
}
