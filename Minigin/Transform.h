#pragma once
#include <glm.hpp>

namespace dae
{
	class GameObject;

	class Transform final
	{
		friend class GameObject;

	public:
		const glm::vec3& GetLocalPosition() const;
		void SetLocalPosition(float x, float y, float z);
		void SetLocalPosition(glm::vec3 pos);

		const glm::vec3& GetWorldPosition();

		void UpdatePosition();
		void SetPositionDirty();
	private:
		glm::vec3 m_localPosition;
		glm::vec3 m_worldPosition;

		bool m_positionDirty;

		GameObject* m_parent = nullptr;
	};
}
