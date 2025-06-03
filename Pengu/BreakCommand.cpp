#include "BreakCommand.h"
#include "EnemyControllerComponent.h"

namespace dae
{
	BreakCommand::BreakCommand(GameObject* gameObject, EnemyControllerComponent* snobee)
		: GameObjectCommand{ gameObject }, m_SnobeeControllerPtr{ snobee }
	{
	}
	void BreakCommand::Execute()
	{
		if (m_buttonState.PressedThisFrame)
			m_SnobeeControllerPtr->Break();
	}
}