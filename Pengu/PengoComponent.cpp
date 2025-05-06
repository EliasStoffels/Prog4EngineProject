#include "PengoComponent.h"
#include "GameObject.h"
#include "TimeSingleton.h"
#include <iostream>

namespace dae
{

	PengoComponent::PengoComponent(float speed) : m_Speed{speed}
	{

	}

	void PengoComponent::Update(float elapsedSec)
	{
		auto transform = m_OwningGameObject->GetTransform();
		glm::vec3 direction = (m_TargetPosition - transform->GetWorldPosition());

		float sqrLength = direction.x * direction.x + direction.y * direction.y;
		if (sqrLength < 4)
		{
			transform->SetLocalPosition(m_TargetPosition - transform->GetWorldPosition() + transform->GetLocalPosition());
		}
		else
		{
			float length = std::sqrt(sqrLength);
			direction.x /= length;
			direction.y /= length;

			direction.x *= (m_Speed * elapsedSec);
			direction.y *= (m_Speed * elapsedSec);



			if (m_TargetPosition.x != FLT_MAX)
				transform->Move(direction);
		}
		
	}

	void PengoComponent::SetTargetPosition(glm::vec3 targetPos)
	{
		if(m_OwningGameObject->GetTransform()->GetWorldPosition() == m_TargetPosition || m_TargetPosition.x == FLT_MAX)
			m_TargetPosition = targetPos;
	}

}
