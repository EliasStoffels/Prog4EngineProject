#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"


dae::GameObject::~GameObject() = default;

void dae::GameObject::Update(float deltaTime)
{
	for (const auto& component : m_OwnedComponents)
	{
		// only call update if implemented
		if (auto* overridden = dynamic_cast<CppBehaviour*>(component.get()))
		{
			overridden->Update(deltaTime);
		}
	}
}

void dae::GameObject::Render() const
{
	for (const auto& component : m_OwnedComponents)
	{
		// only call render if implemented
		if (auto* overridden = dynamic_cast<CppBehaviour*>(component.get()))
		{
			overridden->Render();
		}
	}
	//const auto& pos = m_transform.GetPosition();
	//Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
}

void dae::GameObject::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}

void dae::GameObject::AddComponent(std::unique_ptr<CppBehaviour> component)
{
	if (component)
	{
		m_OwnedComponents.push_back(std::move(component));
	}
}
