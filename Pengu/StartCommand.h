#pragma once
#include "BaseCommand.h"
#include <string>

namespace dae
{
	class StartCommand : public Command
	{
		std::string m_GameModeScenes[3]{ "Pengo", "Versus", "Coop" };
	public:
		StartCommand() = default;
		void Execute() override;

	};

	class TextComponent;
	class ChangeGameModeCommand : public Command
	{
		StartCommand* m_StartCommand = nullptr;
		TextComponent* m_Text = nullptr;

		bool m_Possitive = true;
	public:
		ChangeGameModeCommand(TextComponent* text, StartCommand* startCommand, bool positive);
		void Execute() override;

	};

}

