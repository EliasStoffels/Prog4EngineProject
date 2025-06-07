#pragma once
#include "CppBehaviour.h"
#include "PengoState.h"
#include <memory>

namespace dae
{
    class TextureComponent;
    class GridComponent;
    class PengoComponent : public CppBehaviour
    {
        friend class GameObject;
    public:

        void Start() override;
        void Update(float deltaTime) override;


        void Move(const glm::vec3& direction);
        void Push();
        void Die();
        void Respawn();

        // Getters for states
        TextureComponent* GetTexture() const { return m_TexturePtr; }
        float GetSpeed() const { return m_Speed; }
        glm::vec3 GetDirection() { return m_Direction; }
        GridComponent* GetGrid() const { return m_GridPtr; }

    private:

        PengoComponent(GameObject* owner, float speed, GridComponent* grid);
        float m_Speed;
        GridComponent* m_GridPtr;
        TextureComponent* m_TexturePtr;
        glm::vec3 m_Direction{};

        std::unique_ptr<PengoState> m_CurrentState;
        void ChangeState(std::unique_ptr<PengoState> newState);
    };
}

//#pragma once
//#include "CppBehaviour.h"
//#include "glm.hpp"
//#include "enums.h"
//#include <TextureComponent.h>
//#include "GridComponent.h"
//
//namespace dae
//{
//	class PengoComponent : public CppBehaviour
//	{
//		friend class GameObject;
//
//	public:
//		void Start() override;
//		void Update(float deltaTime) override;
//
//		void SetTargetPosition(glm::vec3 targetPos);
//		void SetRotation(DirectionState rotation);
//		DirectionState GetRotation();
//		void Push();
//
//		virtual ~PengoComponent() = default;
//		PengoComponent(const PengoComponent& other) = delete;
//		PengoComponent(PengoComponent&& other) = delete;
//		PengoComponent& operator=(const PengoComponent& other) = delete;
//		PengoComponent& operator=(PengoComponent&& other) = delete;
//
//	private:
//		PengoComponent(float speed, GridComponent* grid);
//		void Animate(float deltaTime);
//		float m_Speed;
//		DirectionState m_Rotation = DirectionState::Down;
//		PengoActionState m_Animation = PengoActionState::Walking;
//		int m_CurrentFrame = 0;
//		int m_PushFrames = 0;
//		float m_TotalDT = 0.f;
//		const float FRAME_DELAY = 0.1f;
//
//		GridComponent* m_GridPtr = nullptr;
//		TextureComponent* m_TexturePtr = nullptr;
//		glm::vec3 m_TargetPosition{FLT_MAX,FLT_MAX,FLT_MAX};
//
//	};
//}
//
