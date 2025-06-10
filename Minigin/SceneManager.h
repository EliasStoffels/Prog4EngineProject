#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"
#include <functional>
#include "Scene.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name, const std::function<void()>& load);
		Scene& GetScene(const std::string& name = "");
		void LoadScene(const std::string& name);
		
		void Start();
		
		void Update(float deltaTime);
		void FixedUpdate(float fixedTime);
		void Render();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::unique_ptr<Scene>> m_scenes;
		std::vector<std::function<void()>> m_SceneLoaders;
		Scene* m_CurrentScene = nullptr;
	};
}
