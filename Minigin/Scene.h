#pragma once
#include "SceneManager.h"

namespace dae
{
	class GameObject;
	class Scene final
	{
		friend Scene& SceneManager::CreateScene(const std::string& name, const std::function<void()>& load);
	public:
		void Add(std::shared_ptr<GameObject> object);
		void Remove(std::shared_ptr<GameObject> object);
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
		explicit Scene(const std::string& name);

		std::vector < std::shared_ptr<GameObject>> m_objects{};
		std::vector < std::shared_ptr<GameObject>> m_objectsToAdd{};

		static unsigned int m_idCounter; 
	};

}
