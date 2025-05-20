#include "MoveCommand.h"
#include "TimeSingleton.h"
#include <iostream>
#include "../Pengu/PengoComponent.h"
#include "../Pengu/GridComponent.h"

namespace dae
{
	MoveCommand::MoveCommand(GameObject* gameObject, const glm::vec3& direction, PengoComponent* pengo)
		: GameObjectCommand{ gameObject }, m_Direction{ direction }, m_Pengo{pengo}
	{
		
	}

	void MoveCommand::Execute()
	{
		m_Pengo->Move(m_Direction);
	}
}
