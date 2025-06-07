#include "RespawnCommand.h"
#include "PengoComponent.h"
#include "EnemyControllerComponent.h"
#include "GameStateManager.h"

namespace dae
{
	RespawnCommand::RespawnCommand(PengoComponent* pengo, EnemyControllerComponent* enemyController) : m_PengoPtr{pengo}, m_EnemyControllerPtr{enemyController}
	{
	}
	void RespawnCommand::Execute()
	{
		if (m_buttonState.ReleasedThisFrame && GameStateManager::GetInstance().playersDead)
		{
			m_PengoPtr->Respawn();
			m_EnemyControllerPtr->ResetEnemyPos();
			GameStateManager::GetInstance().playersDead = false;
		}
	}
}