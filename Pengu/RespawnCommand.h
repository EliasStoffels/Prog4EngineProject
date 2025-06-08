#pragma once
#include "BaseCommand.h"

namespace dae
{
	class PengoComponent;
	class EnemyControllerComponent;
	class RespawnCommand : public GameObjectCommand
	{
		/*PengoComponent* m_PengoPtr = nullptr;
		EnemyControllerComponent* m_EnemyControllerPtr = nullptr;*/
	public:
		RespawnCommand(GameObject* gameObject);
		void Execute() override;

	};
}

