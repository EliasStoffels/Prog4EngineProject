#include "MoveCommand.h"
#include "TimeSingleton.h"
#include <iostream>

namespace dae
{
	MoveCommand::MoveCommand(GameObject* gameObject, float speed, glm::vec2 direction)
		: GameObjectCommand{ gameObject }, m_Speed{ speed }, m_Direction{ direction }
	{
	}

	void MoveCommand::Execute()
	{
		auto goTransform = GetGameObject()->GetTransform();
		auto desiredPos = goTransform->GetWorldPosition() + glm::vec3{ m_Direction.x * m_Speed * TimeSingleton::GetInstance().GetDeltaTime(),m_Direction.y * m_Speed * TimeSingleton::GetInstance().GetDeltaTime() ,0 };

		goTransform->Move(glm::vec3{m_Direction.x * m_Speed * TimeSingleton::GetInstance().GetDeltaTime(),m_Direction.y * m_Speed * TimeSingleton::GetInstance().GetDeltaTime() ,0 });

	}
}
