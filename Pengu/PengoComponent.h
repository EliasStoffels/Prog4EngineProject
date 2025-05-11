#pragma once
#include "CppBehaviour.h"
#include "glm.hpp"
#include "enums.h"
#include <TextureComponent.h>
#include "GridComponent.h"

namespace dae
{
	class PengoComponent : public CppBehaviour
	{
		friend class GameObject;

	public:
		void Start() override;
		void Update(float deltaTime) override;

		void SetTargetPosition(glm::vec3 targetPos);
		void SetRotation(PengoRotationState rotation);
		PengoRotationState GetRotation();
		void Push();

		virtual ~PengoComponent() = default;
		PengoComponent(const PengoComponent& other) = delete;
		PengoComponent(PengoComponent&& other) = delete;
		PengoComponent& operator=(const PengoComponent& other) = delete;
		PengoComponent& operator=(PengoComponent&& other) = delete;

	private:
		PengoComponent(float speed, GridComponent* grid);
		void Animate(float deltaTime);
		float m_Speed;
		PengoRotationState m_Rotation = PengoRotationState::Down;
		PengoAnimationState m_Animation = PengoAnimationState::Walking;
		int m_CurrentFrame = 0;
		int m_PushFrames = 0;
		float m_TotalDT = 0.f;
		const float FRAME_DELAY = 0.1f;

		GridComponent* m_GridPtr = nullptr;
		TextureComponent* m_TexturePtr = nullptr;
		glm::vec3 m_TargetPosition{FLT_MAX,FLT_MAX,FLT_MAX};

	};
}

