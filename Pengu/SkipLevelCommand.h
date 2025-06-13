#pragma once
#include <BaseCommand.h>

namespace dae
{
	class SkipLevelCommand : public GameObjectCommand
	{

	public:
		SkipLevelCommand(GameObject* gameObject);
		void Execute() override;
	};

}

