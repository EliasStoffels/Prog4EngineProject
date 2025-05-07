#include "MoveCommand.h"
#include "TimeSingleton.h"
#include <iostream>
#include "../Pengu/PengoComponent.h"
#include "../Pengu/GridComponent.h"

namespace dae
{
	MoveCommand::MoveCommand(GameObject* gameObject, const glm::vec2& direction, GridComponent* grid, PengoComponent* pengo)
		: GameObjectCommand{ gameObject }, m_Direction{ direction },m_Grid{grid}, m_Pengo{pengo}, m_Rotation{}
	{
		m_Rotation = VecToRotation(direction);
		
	}

	void MoveCommand::Execute()
	{
		auto goTransform = GetGameObject()->GetTransform();
		auto currentPos = goTransform->GetWorldPosition();

		m_Pengo->SetRotation(m_Rotation);
		m_Pengo->SetTargetPosition(m_Grid->RequestMove(currentPos, m_Direction));
	}
}
