#include "KillEnemyCommand.h"
#include "ServiceLocator.h"

namespace dae
{
	KillEnemyCommand::KillEnemyCommand(GameObject* gameObject) : GameObjectCommand{ gameObject }
	{
		m_ScoreComponent = gameObject->GetComponent<ScoreComponent>();
	}

	void KillEnemyCommand::Execute()
	{
		//if (m_buttonState.ReleasedThisFrame)
		//	dae::ServiceLocator::GetInstance().GetSoundSystem().PlayLooping(static_cast<dae::sound_id>(dae::make_sdbm_hash("BGMusic")), 100.f);

	}
}
