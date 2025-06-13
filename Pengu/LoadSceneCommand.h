#pragma once
#include <BaseCommand.h>
#include <string>

namespace dae
{
	class LoadSceneCommand : public Command
	{
		std::string m_Scene{};
	public:
		LoadSceneCommand(const std::string& sceneName);
		void Execute() override;
	};
}

