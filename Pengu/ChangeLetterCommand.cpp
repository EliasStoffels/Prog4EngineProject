#include "ChangeLetterCommand.h"
#include "HighScoreNameComponent.h"

void dae::ChangeLetterCommand::Execute()
{
	if(m_buttonState.ReleasedThisFrame)
		m_NameComponent->ChangeLetter(m_SelectedLetter, m_Increase); 
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

void dae::ChangeSelectedLetterCommand::Execute()
{
	if(m_buttonState.ReleasedThisFrame)
	for(auto command : m_ChangeLetterCommands)
		command->ChangeSelectedLetter(m_GoNext);
}

dae::ChangeSelectedLetterCommand::ChangeSelectedLetterCommand(std::vector<ChangeLetterCommand*> changeLetterCommand, bool goNext) : m_ChangeLetterCommands{changeLetterCommand}, m_GoNext{goNext}
{

}
