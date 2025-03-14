#include "DieCommand.h"

namespace dae
{
	DieCommand::DieCommand(GameObject* gameObject) : GameObjectCommand{ gameObject }
	{
		m_HealthComponent = gameObject->GetComponent<HealthComponent>();
	}

	void DieCommand::Execute()
	{
		if (m_buttonState.ReleasedThisFrame)
			m_HealthComponent->TakeDamage(100.f);
	}
}
