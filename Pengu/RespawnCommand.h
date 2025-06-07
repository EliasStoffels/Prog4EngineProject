#pragma once
#include "BaseCommand.h"

namespace dae
{
	class PengoComponent;
	class EnemyControllerComponent;
	class RespawnCommand : public Command
	{
		PengoComponent* m_PengoPtr = nullptr;
		EnemyControllerComponent* m_EnemyControllerPtr = nullptr;
	public:
		RespawnCommand(PengoComponent* pengo, EnemyControllerComponent* enemyController);
		void Execute() override;

	};
}

