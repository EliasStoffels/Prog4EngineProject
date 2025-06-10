#include "SceneManager.h"
//#include "Scene.h"
#include <algorithm>
#include <stdexcept>
#include "InputManager.h"


void dae::SceneManager::Update(float deltaTime)
{
	if (!m_CurrentScene->startCalled)
	{
		m_CurrentScene->startCalled = true;
		m_CurrentScene->Start();
	}
	m_CurrentScene->Update(deltaTime);
	/*for(auto& scene : m_scenes)
	{
		scene->Update(deltaTime);
	}*/
}

void dae::SceneManager::FixedUpdate(float fixedTime)
{
	m_CurrentScene->FixedUpdate(fixedTime);

	/*for (auto& scene : m_scenes)
	{
		scene->FixedUpdate(fixedTime);
	}*/
}

void dae::SceneManager::Render()
{
	m_CurrentScene->Render();
	/*for (const auto& scene : m_scenes)
	{
		scene->Render();
	}*/
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name, const std::function<void()>& load)
{
	auto it = std::find_if(m_scenes.begin(), m_scenes.end(),
		[&name](const std::unique_ptr<Scene>& scene) {
			return scene->name == name;
		});

	if(it != m_scenes.end())
		throw std::runtime_error("Scene already exists: " + name);

	m_scenes.emplace_back(std::make_unique<Scene>(name));
	auto& scene = *m_scenes.back();

	m_SceneLoaders.push_back(load);
	if (!m_CurrentScene)
		m_CurrentScene = &scene;

	return scene;
}

dae::Scene& dae::SceneManager::GetScene(const std::string& name)
{
	if (name == "")
		return *m_CurrentScene;

	 auto it = std::find_if(m_scenes.begin(), m_scenes.end(),
        [&name](const std::unique_ptr<Scene>& scene) {
            return scene->name == name;
        });

    if (it == m_scenes.end())
        throw std::runtime_error("Scene not found: " + name);

    return **it; 
}

void dae::SceneManager::LoadScene(const std::string& name)
{
	m_CurrentScene->UnloadScene();
	InputManager::GetInstance().ClearCommands();

	auto it = std::find_if(m_scenes.begin(), m_scenes.end(),
		[&name](const std::unique_ptr<Scene>& scene) {
			return scene->name == name;
		});

	if (it == m_scenes.end())
		throw std::runtime_error("Scene not found: " + name);

	m_CurrentScene = it->get();
	int idx = std::distance(m_scenes.begin(), it);
	m_SceneLoaders[idx]();

}

void dae::SceneManager::Start()
{
	m_CurrentScene->startCalled = true;
	m_CurrentScene->Start();
	/*for (const auto& scene : m_scenes)
	{
		scene->Start();
	}*/
}
