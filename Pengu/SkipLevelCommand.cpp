#include "SkipLevelCommand.h"

dae::SkipLevelCommand::SkipLevelCommand(GameObject* gameObject): GameObjectCommand{gameObject}
{
}

void dae::SkipLevelCommand::Execute()
{
	if(m_buttonState.ReleasedThisFrame)
		GetGameObject()->NotifyObservers(Event{ make_sdbm_hash("LevelWon"), nullptr });
}
