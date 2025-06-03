#pragma once
#include "BaseCommand.h"
#include <iostream>

namespace dae
{
	class StartCommand : public Command
	{
	public:
		StartCommand();
		void Execute() override;
	};

}

