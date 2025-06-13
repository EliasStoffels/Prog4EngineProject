#pragma once
#include <BaseCommand.h>

namespace dae
{
	class HighScoreNameComponent;
	class ChangeLetterCommand : public Command
	{
		HighScoreNameComponent* m_NameComponent;
		int m_SelectedLetter = 0;
		bool m_Increase = true;
	public:
		void Execute() override;
		void ChangeSelectedLetter(bool goNext);
		ChangeLetterCommand(HighScoreNameComponent* nameComponent,bool increase);
	};

	class ChangeSelectedLetterCommand : public Command
	{
		bool m_GoNext = true;
		std::vector<ChangeLetterCommand*> m_ChangeLetterCommands;
	public:
		void Execute() override;
		ChangeSelectedLetterCommand(std::vector<ChangeLetterCommand*> changeLetterCommand, bool goNext);
	};
}

