#include "Scene.h"
#include "GameObject.h"

#include <algorithm>

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : name(name) {}

Scene::~Scene() = default;

void Scene::Add(std::shared_ptr<GameObject> object)
{
	m_objects.emplace_back(std::move(object));
}

void Scene::Remove(std::shared_ptr<GameObject> object)
{
	m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

void dae::Scene::Start()
{
	for (auto& object : m_objects)
	{
		object->Start();
	}
}

void Scene::Update(float deltaTime)
{
	for(auto& object : m_objects)
	{
		object->Update(deltaTime);
	}

	for (auto& object : m_objects)
	{
		object->LateUpdate(deltaTime);
	}

	auto removeIter = std::remove_if(m_objects.begin(), m_objects.end(),
		[](const std::shared_ptr <GameObject>& object) { return object->pendingRemove; });
	m_objects.erase(removeIter, m_objects.end());
}

void dae::Scene::FixedUpdate(float fixedTime)
{
	for (auto& object : m_objects)
	{
		object->FixedUpdate(fixedTime);
	}
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}

