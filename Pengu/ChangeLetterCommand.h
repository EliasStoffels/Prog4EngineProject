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
		ChangeLetterCommand* m_ChangeLetterCommand;
	public:
		void Execute() override;
		ChangeSelectedLetterCommand(ChangeLetterCommand* changeLetterCommand);
	};
}

