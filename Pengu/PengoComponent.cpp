#include "PengoComponent.h"
#include "GameObject.h"
#include "TimeSingleton.h"
#include <iostream>

namespace dae
{

	PengoComponent::PengoComponent(float speed, GridComponent* grid) : m_Speed{speed},m_GridPtr{grid}
	{

	}

	void PengoComponent::Start()
	{
		m_TexturePtr = m_OwningGameObject->GetComponent<TextureComponent>();
	}

	void PengoComponent::Update(float deltaTime)
	{
		auto transform = m_OwningGameObject->GetTransform();
		glm::vec3 direction = (m_TargetPosition - transform->GetWorldPosition());

		float sqrLength = direction.x * direction.x + direction.y * direction.y;
		if (sqrLength < 4)
		{
			transform->SetLocalPosition(m_TargetPosition - transform->GetWorldPosition() + transform->GetLocalPosition());
		}
		else if (m_Animation == PengoAnimationState::Walking)
		{
			float length = std::sqrt(sqrLength);
			direction.x /= length;
			direction.y /= length;

			direction.x *= (m_Speed * deltaTime);
			direction.y *= (m_Speed * deltaTime);

			if (m_TargetPosition.x != FLT_MAX)
				transform->Move(direction);
		}

		Animate(deltaTime);
	}

	void PengoComponent::SetTargetPosition(glm::vec3 targetPos)
	{
		if((m_OwningGameObject->GetTransform()->GetWorldPosition() == m_TargetPosition || m_TargetPosition.x == FLT_MAX) && m_Animation == PengoAnimationState::Walking)
			m_TargetPosition = targetPos;
	}

	void PengoComponent::SetRotation(PengoRotationState rotation)
	{
		if(m_OwningGameObject->GetTransform()->GetWorldPosition() == m_TargetPosition && m_TargetPosition.x != FLT_MAX && m_Animation == PengoAnimationState::Walking)
			m_Rotation = rotation;
	}

	PengoRotationState PengoComponent::GetRotation()
	{
		return m_Rotation;
	}

	void PengoComponent::Push()
	{
		if (m_OwningGameObject->GetTransform()->GetWorldPosition() == m_TargetPosition &&
			m_GridPtr->RequestPush(m_OwningGameObject->GetWorldPosition(), RotationToVec3(m_Rotation),m_pushFrames))
		{
			m_Animation = PengoAnimationState::Pushing;
			m_CurrentFrame = -1;
		}
		
	}

	void PengoComponent::Animate(float deltaTime)
	{
		m_TotalDT += deltaTime;
		if (m_TotalDT > FRAME_DELAY)
		{
			m_TotalDT -= FRAME_DELAY;
			
			switch (m_Animation)
			{
			case PengoAnimationState::Walking:
			{
				if (m_OwningGameObject->GetWorldPosition() != m_TargetPosition && m_TargetPosition.x != FLT_MAX)
					++m_CurrentFrame %= 2;
				else
					m_CurrentFrame = 0;
				int currentFrameOffset = 16 * m_CurrentFrame;
				switch (m_Rotation)
				{
				case PengoRotationState::Left:
				{
					m_TexturePtr->SetSourceRect(32 + currentFrameOffset, 0);
				}
				break;
				case PengoRotationState::Right:
				{
					m_TexturePtr->SetSourceRect(96 + currentFrameOffset, 0);
				}
				break;
				case PengoRotationState::Up:
				{
					m_TexturePtr->SetSourceRect(currentFrameOffset, 0);
				}
				break;
				case PengoRotationState::Down:
				{
					m_TexturePtr->SetSourceRect(64 + currentFrameOffset, 0);
				}
				break;
				}
			}
			break;
			case PengoAnimationState::Pushing:
			{
				++m_CurrentFrame;
				if (m_CurrentFrame == m_pushFrames)
					m_Animation = PengoAnimationState::Walking;
				int currentFrameOffset = 16 * (m_CurrentFrame % 2);
				switch (m_Rotation)
				{
				case PengoRotationState::Left:
				{
					m_TexturePtr->SetSourceRect(32 + currentFrameOffset, 16);
				}
				break;
				case PengoRotationState::Right:
				{
					m_TexturePtr->SetSourceRect(96 + currentFrameOffset, 16);
				}
				break;
				case PengoRotationState::Up:
				{
					m_TexturePtr->SetSourceRect(currentFrameOffset, 16);
				}
				break;
				case PengoRotationState::Down:
				{
					m_TexturePtr->SetSourceRect(64 + currentFrameOffset, 16);
				}
				break;
				}
			}
			break;
			case PengoAnimationState::Dying:
			{
				switch (m_Rotation)
				{
				case PengoRotationState::Left:
				{

				}
				break;
				case PengoRotationState::Right:
				{
					
				}
				break;
				case PengoRotationState::Up:
				{
					
				}
				break;
				case PengoRotationState::Down:
				{
					
				}
				break;
				}
			}
			break;
			}
		}

		
	}

}
