#include "KillEnemyCommand.h"

namespace dae
{
	KillEnemyCommand::KillEnemyCommand(GameObject* gameObject) : GameObjectCommand{ gameObject }
	{
	}

	void KillEnemyCommand::Execute()
	{
		//if (m_buttonState.ReleasedThisFrame)
	}
}
