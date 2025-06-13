#pragma once
#include <BaseCommand.h>

namespace dae
{
	class MuteSoundCommand : public Command
	{
		bool m_Muted = false;
	public:
		MuteSoundCommand() = default;
		void Execute() override;
	};

}

