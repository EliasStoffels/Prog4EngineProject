#include "BreakCommand.h"
#include "EnemyComponent.h"

namespace dae
{
	BreakCommand::BreakCommand(GameObject* gameObject, EnemyComponent* snobee)
		: GameObjectCommand{ gameObject }, m_SnobeePtr{ snobee }
	{
	}
	void BreakCommand::Execute()
	{
		if (m_buttonState.PressedThisFrame)
			m_SnobeePtr->Break();
	}
}