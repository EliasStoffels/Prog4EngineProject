#include "KillEnemyCommand.h"

namespace dae
{
	KillEnemyCommand::KillEnemyCommand(GameObject* gameObject) : GameObjectCommand{ gameObject }
	{
		m_ScoreComponent = gameObject->GetComponent<ScoreComponent>();
	}

	void KillEnemyCommand::Execute()
	{
		if (m_buttonState.ReleasedThisFrame)
			m_ScoreComponent->ChangeScore(500);
	}
}
