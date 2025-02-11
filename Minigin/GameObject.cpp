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

void dae::GameObject::Render() const
{
	for (const auto& component : m_OwnedComponents)
	{
		component->Render();
	}
	//const auto& pos = m_transform.GetPosition();
	//Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
}

//void dae::GameObject::SetTexture(const std::string& filename)
//{
//	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
//}

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}

dae::Transform dae::GameObject::GetTransform()
{
	return m_transform;
}

void dae::GameObject::AddComponent(std::unique_ptr<CppBehaviour> component)
{
	if (component)
	{
		component->SetOwningGameObject(this);
		m_OwnedComponents.push_back(std::move(component));
	}
}
