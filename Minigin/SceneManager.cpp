#include "SceneManager.h"
#include "Scene.h"
#include <algorithm>
#include <stdexcept>

void dae::SceneManager::Update(float deltaTime)
{
	for(auto& scene : m_scenes)
	{
		scene->Update(deltaTime);
	}
}

void dae::SceneManager::FixedUpdate(float fixedTime)
{
	for (auto& scene : m_scenes)
	{
		scene->FixedUpdate(fixedTime);
	}
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_scenes)
	{
		scene->Render();
	}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	return *scene;
}

dae::Scene& dae::SceneManager::GetScene(const std::string& name)
{
	 auto it = std::find_if(m_scenes.begin(), m_scenes.end(),
        [&name](const std::shared_ptr<Scene>& scene) {
            return scene->name == name;
        });

    if (it == m_scenes.end())
        throw std::runtime_error("Scene not found: " + name);

    return **it; 
}

void dae::SceneManager::Start()
{
	for (const auto& scene : m_scenes)
	{
		scene->Start();
	}
}
