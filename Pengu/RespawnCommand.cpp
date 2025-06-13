#include "RespawnCommand.h"
#include "PengoComponent.h"
#include "EnemyControllerComponent.h"
#include "GameStateManager.h"
#include <iostream>

namespace dae
{
	RespawnCommand::RespawnCommand(GameObject* gameObject) : GameObjectCommand{gameObject}
	{
	}
	void RespawnCommand::Execute()
	{
		if (m_buttonState.ReleasedThisFrame && GameStateManager::GetInstance().playersDead)
		{
			GetGameObject()->NotifyObservers(Event{ make_sdbm_hash("Respawn"), nullptr });
		}
	}
}