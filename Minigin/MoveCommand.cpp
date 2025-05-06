#include "MoveCommand.h"
#include "TimeSingleton.h"
#include <iostream>

namespace dae
{
	MoveCommand::MoveCommand(GameObject* gameObject, float speed, const glm::vec2& direction, GridComponent* grid, PengoComponent* pengo)
		: GameObjectCommand{ gameObject }, m_Speed{ speed }, m_Direction{ direction },m_Grid{grid}
	{
		m_Pengo = pengo;
	}

	void MoveCommand::Execute()
	{
		auto goTransform = GetGameObject()->GetTransform();
		auto currentPos = goTransform->GetWorldPosition();
		//auto desiredPos = currentPos + glm::vec3{ m_Direction.x * m_Speed * TimeSingleton::GetInstance().GetDeltaTime(),m_Direction.y * m_Speed * TimeSingleton::GetInstance().GetDeltaTime() ,0 };
		
		m_Pengo->SetTargetPosition(m_Grid->RequestMove(currentPos, m_Direction));

		//if (m_Grid->RequestMove(currentPos, glm::vec2{ m_Direction.x,m_Direction.y }))
		//{
		//	goTransform->Move(glm::vec3{ m_Direction.x * m_Speed * TimeSingleton::GetInstance().GetDeltaTime(),m_Direction.y * m_Speed * TimeSingleton::GetInstance().GetDeltaTime() ,0 });
		//}
		//goTransform->Move(glm::vec3{m_Direction.x * m_Speed * TimeSingleton::GetInstance().GetDeltaTime(),m_Direction.y * m_Speed * TimeSingleton::GetInstance().GetDeltaTime() ,0 });

	}
}
