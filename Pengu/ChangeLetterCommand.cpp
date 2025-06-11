#include "ChangeLetterCommand.h"

void dae::ChangeLetterCommand::Execute()
{

}

void dae::ChangeLetterCommand::ChangeSelectedLetter(bool goNext)
{
	if (goNext)
	{
		m_SelectedLetter = (++m_SelectedLetter) % 3;
	}
	else
	{
		--m_SelectedLetter;
		if (m_SelectedLetter < 0)
			m_SelectedLetter = 2;
	}
}

dae::ChangeLetterCommand::ChangeLetterCommand(HighScoreNameComponent* nameComponent, bool increase) : m_Increase{ increase }, m_NameComponent{ nameComponent }
{

}

dae::ChangeSelectedLetterCommand::ChangeSelectedLetterCommand(ChangeLetterCommand* changeLetterCommand) : m_ChangeLetterCommand{changeLetterCommand}
{

}
