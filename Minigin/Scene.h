#pragma once
//#include "SceneManager.h"
#include <memory>
#include <string>
#include <vector>
#include <functional>
#include "GameObject.h"

namespace dae
{
	class SceneManager;
	class Scene final
	{
		//friend Scene& SceneManager::CreateScene(const std::string& name, const std::function<void()>& load);
	public:
		explicit Scene(const std::string& name);
		GameObject* AddEmpty();
		void Remove(std::unique_ptr<GameObject> object);
		void RemoveAll();

		void Start();

		void Update(float deltaTime);
		void FixedUpdate(float fixedTime);
		void Render() const;
		void UnloadScene();
		void SetSortDirty();

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		bool startCalled = false;
		std::string name;
	private:
		bool m_NeedsSort = true;

		std::vector < std::unique_ptr<GameObject>> m_objects{};
		std::vector < std::unique_ptr<GameObject>> m_objectsToAdd{};

		static unsigned int m_idCounter; 
	};

}
