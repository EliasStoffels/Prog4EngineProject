#pragma once
#include <glm.hpp>
#include <vector>

namespace dae
{
	class GameObject;

	class Transform final
	{
		friend class GameObject;

	public:
		const glm::vec3& GetLocalPosition() const;
		void SetWorldPosition(float x, float y, float z);
		void SetWorldPosition(glm::vec3 pos);
		void SetLocalPosition(float x, float y, float z);
		void SetLocalPosition(glm::vec3 pos);

		GameObject* GetParent();
		const glm::vec3& GetWorldPosition();
		void Move(glm::vec3 direction);

	private:
		void UpdatePosition();
		void SetPositionDirty();
		glm::vec3 m_localPosition{};
		glm::vec3 m_worldPosition{};

		bool m_positionDirty = false;

		GameObject* m_parent = nullptr;
		std::vector<GameObject*>* m_childObjects = nullptr;
	};
}
