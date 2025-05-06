#pragma once
#include "CppBehaviour.h"
#include "glm.hpp"

namespace dae
{

	class PengoComponent : public CppBehaviour
	{
		friend class GameObject;

	public:
		void Update(float elapsedSec) override;

		void SetTargetPosition(glm::vec3 targetPos);

		virtual ~PengoComponent() = default;
		PengoComponent(const PengoComponent& other) = delete;
		PengoComponent(PengoComponent&& other) = delete;
		PengoComponent& operator=(const PengoComponent& other) = delete;
		PengoComponent& operator=(PengoComponent&& other) = delete;

	private:
		PengoComponent(float speed);
		float m_Speed;

		glm::vec3 m_TargetPosition{FLT_MAX,FLT_MAX,FLT_MAX};

	};
}

