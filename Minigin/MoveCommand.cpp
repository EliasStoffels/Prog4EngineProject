#include "MoveCommand.h"
#include "TimeSingleton.h"
#include <iostream>

namespace dae
{
	MoveCommand::MoveCommand(GameObject* gameObject, float speed, Direction direction)
		: GameObjectCommand{ gameObject }, m_Speed{ speed }, m_Direction{ direction }
	{
	}

	void MoveCommand::Execute()
	{
		auto goTransform = GetGameObject()->GetTransform();
		switch (m_Direction)
		{
		case Direction::Up:
		{
			goTransform->Move(glm::vec3{ 0,-m_Speed * TimeSingleton::GetInstance().GetDeltaTime() ,0 });
		}
		break;
		case Direction::Down:
		{
			goTransform->Move(glm::vec3{ 0,m_Speed * TimeSingleton::GetInstance().GetDeltaTime() ,0 });
		}
		break;
		case Direction::Left:
		{
			goTransform->Move(glm::vec3{ -m_Speed * TimeSingleton::GetInstance().GetDeltaTime(),0 ,0 });
		}
		break;
		case Direction::Right:
		{
			goTransform->Move(glm::vec3{ m_Speed * TimeSingleton::GetInstance().GetDeltaTime(),0 ,0 });
		}
		break;
		}


	}
}
