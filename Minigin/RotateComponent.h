#pragma once
#include "CppBehaviour.h"

namespace dae
{
	class RotateComponent : public CppBehaviour
	{
		friend class GameObject;

	public:
		void Update(float deltaTime) override;

		void SetRadius(float radius);
		void SetRadianPerSecond(float radianPerSecond);
		void SetDegreePerSecond(float degreePerSecond);

		virtual ~RotateComponent() = default;
		RotateComponent(const RotateComponent& other) = delete;
		RotateComponent(RotateComponent&& other) = delete;
		RotateComponent& operator=(const RotateComponent& other) = delete;
		RotateComponent& operator=(RotateComponent&& other) = delete;

	private:
		RotateComponent();
		float m_totalDeltaTime{};
		float m_radius = 0.f;
		float m_radianPerSecond = 0.f;
	};
}

