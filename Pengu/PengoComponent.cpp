#include "PengoComponent.h"
#include "PengoState.h"
#include "GameObject.h"
#include "TimeSingleton.h"
#include "TextureComponent.h"
#include <iostream>

namespace dae
{
    PengoComponent::PengoComponent(GameObject* owner, float speed, GridComponent* grid)
        : CppBehaviour{ owner }, m_Speed {
        speed
    }, m_GridPtr{ grid }, m_TexturePtr{ nullptr }
    {
        m_CurrentState = std::make_unique<PengoWalkingState>();
    }

    void PengoComponent::Start()
    {
        m_TexturePtr = m_OwningGameObject->GetComponent<TextureComponent>();
        m_CurrentState->Enter(this);
    }

    void PengoComponent::Update(float deltaTime)
    {
        auto newState = m_CurrentState->Update(this, deltaTime);
        if (newState)
            ChangeState(std::move(newState));
    }

    void PengoComponent::Move(const glm::vec3& direction)
    {
        m_Direction = direction;
        auto newState = m_CurrentState->OnMove(this);
        if (newState)
            ChangeState(std::move(newState));
    }

    void PengoComponent::Push()
    {
        auto newState = m_CurrentState->OnPush(this);
        if (newState)
            ChangeState(std::move(newState));
    }

    void PengoComponent::Die()
    {
        auto newState = m_CurrentState->Die(this);
        if (newState)
            ChangeState(std::move(newState));
    }

    void PengoComponent::Respawn()
    {
        auto newState = m_CurrentState->Respawn(this);
        if (newState)
            ChangeState(std::move(newState));
    }

    void PengoComponent::ChangeState(std::unique_ptr<PengoState> newState)
    {
        m_CurrentState->Exit(this);
        m_CurrentState = std::move(newState);
        m_CurrentState->Enter(this);
    }
}


//#include "PengoComponent.h"
//#include "GameObject.h"
//#include "TimeSingleton.h"
//#include <iostream>
//
//namespace dae
//{
//
//	PengoComponent::PengoComponent(float speed, GridComponent* grid) : m_Speed{speed},m_GridPtr{grid}
//	{
//
//	}
//
//	void PengoComponent::Start()
//	{
//		m_TexturePtr = m_OwningGameObject->GetComponent<TextureComponent>();
//	}
//
//	void PengoComponent::Update(float deltaTime)
//	{
//		auto transform = m_OwningGameObject->GetTransform();
//		glm::vec3 direction = (m_TargetPosition - transform->GetWorldPosition());
//
//		float sqrLength = glm::dot(direction,direction);
//		if (sqrLength < 4)
//		{
//			transform->SetLocalPosition(m_TargetPosition - transform->GetWorldPosition() + transform->GetLocalPosition());
//		}
//		else if (m_Animation == PengoActionState::Walking)
//		{
//			float length = std::sqrt(sqrLength);
//			direction.x /= length;
//			direction.y /= length;
//
//			direction.x *= (m_Speed * deltaTime);
//			direction.y *= (m_Speed * deltaTime);
//
//			if (m_TargetPosition.x != FLT_MAX)
//				transform->Move(direction);
//		}
//
//		Animate(deltaTime);
//	}
//
//	void PengoComponent::SetTargetPosition(glm::vec3 targetPos)
//	{
//		if((m_OwningGameObject->GetTransform()->GetWorldPosition() == m_TargetPosition || m_TargetPosition.x == FLT_MAX) && m_Animation == PengoActionState::Walking)
//			m_TargetPosition = targetPos;
//	}
//
//	void PengoComponent::SetRotation(DirectionState rotation)
//	{
//		if(m_OwningGameObject->GetTransform()->GetWorldPosition() == m_TargetPosition && m_TargetPosition.x != FLT_MAX && m_Animation == PengoActionState::Walking)
//			m_Rotation = rotation;
//	}
//
//	DirectionState PengoComponent::GetRotation()
//	{
//		return m_Rotation;
//	}
//
//	void PengoComponent::Push()
//	{
//		glm::vec3 distanceVec = m_OwningGameObject->GetWorldPosition() - m_TargetPosition;
//		float sqrLength = glm::dot(distanceVec, distanceVec);
//		if (sqrLength < 100)
//		{
//			m_OwningGameObject->SetLocalPosition(m_TargetPosition - m_OwningGameObject->GetWorldPosition() + m_OwningGameObject->GetLocalPosition());
//			auto blockState = m_GridPtr->RequestPush(m_OwningGameObject->GetWorldPosition(), RotationToVec3(m_Rotation));
//			switch (blockState)
//			{
//			case BlockState::Sliding:
//			{
//				m_PushFrames = 1;
//				m_Animation = PengoActionState::Pushing;
//				m_CurrentFrame = -1;
//			}
//			break;
//			case BlockState::Breaking:
//			{
//				m_PushFrames = 5;
//				m_Animation = PengoActionState::Pushing;
//				m_CurrentFrame = -1;
//			}
//			break;
//			}
//			
//		}
//		
//	}
//
//	void PengoComponent::Animate(float deltaTime)
//	{
//		m_TotalDT += deltaTime;
//		if (m_TotalDT > FRAME_DELAY)
//		{
//			m_TotalDT -= FRAME_DELAY;
//			
//			switch (m_Animation)
//			{
//			case PengoActionState::Walking:
//			{
//				if (m_OwningGameObject->GetWorldPosition() != m_TargetPosition && m_TargetPosition.x != FLT_MAX)
//					++m_CurrentFrame %= 2;
//				else
//					m_CurrentFrame = 0;
//				int currentFrameOffset = 16 * m_CurrentFrame;
//				switch (m_Rotation)
//				{
//				case DirectionState::Left:
//				{
//					m_TexturePtr->SetSourceRect(32 + currentFrameOffset, 0);
//				}
//				break;
//				case DirectionState::Right:
//				{
//					m_TexturePtr->SetSourceRect(96 + currentFrameOffset, 0);
//				}
//				break;
//				case DirectionState::Up:
//				{
//					m_TexturePtr->SetSourceRect(currentFrameOffset, 0);
//				}
//				break;
//				case DirectionState::Down:
//				{
//					m_TexturePtr->SetSourceRect(64 + currentFrameOffset, 0);
//				}
//				break;
//				}
//			}
//			break;
//			case PengoActionState::Pushing:
//			{
//				++m_CurrentFrame;
//				if (m_CurrentFrame == m_PushFrames)
//					m_Animation = PengoActionState::Walking;
//				int currentFrameOffset = 16 * (m_CurrentFrame % 2);
//				switch (m_Rotation)
//				{
//				case DirectionState::Left:
//				{
//					m_TexturePtr->SetSourceRect(32 + currentFrameOffset, 16);
//				}
//				break;
//				case DirectionState::Right:
//				{
//					m_TexturePtr->SetSourceRect(96 + currentFrameOffset, 16);
//				}
//				break;
//				case DirectionState::Up:
//				{
//					m_TexturePtr->SetSourceRect(currentFrameOffset, 16);
//				}
//				break;
//				case DirectionState::Down:
//				{
//					m_TexturePtr->SetSourceRect(64 + currentFrameOffset, 16);
//				}
//				break;
//				}
//			}
//			break;
//			case PengoActionState::Dying:
//			{
//				switch (m_Rotation)
//				{
//				case DirectionState::Left:
//				{
//
//				}
//				break;
//				case DirectionState::Right:
//				{
//					
//				}
//				break;
//				case DirectionState::Up:
//				{
//					
//				}
//				break;
//				case DirectionState::Down:
//				{
//					
//				}
//				break;
//				}
//			}
//			break;
//			}
//		}
//
//		
//	}
//
//}
