#include "StartCommand.h"
#include "SceneManager.h"
#include <iostream>
#include "GameStateManager.h"
#include "TextComponent.h"

namespace dae
{

	void dae::StartCommand::Execute()
	{
		if(m_buttonState.ReleasedThisFrame)
			dae::SceneManager::GetInstance().LoadScene(m_GameModeScenes[GameStateManager::GetInstance().currentGameModeIdx]);
	}

	ChangeGameModeCommand::ChangeGameModeCommand(TextComponent* text, StartCommand* startCommand, bool positive) : m_Text{ text }, m_StartCommand { startCommand }, m_Possitive{ positive }
	{

	}

	void ChangeGameModeCommand::Execute()
	{
		if(m_buttonState.ReleasedThisFrame)
		{
			GameStateManager::GetInstance().currentGameModeIdx = m_Possitive ? (GameStateManager::GetInstance().currentGameModeIdx + 1) % 3 : (GameStateManager::GetInstance().currentGameModeIdx - 1);
			if (GameStateManager::GetInstance().currentGameModeIdx < 0) GameStateManager::GetInstance().currentGameModeIdx = 2;

			switch (GameStateManager::GetInstance().currentGameModeIdx % 3)
			{
			case 0:
			{
				m_Text->SetText("1 Player only");
			}
			break;
			case 1:
			{
				m_Text->SetText("2 Player versus");
			}
			break;
			case 2:
			{
				m_Text->SetText("2 Player coop");
			}
			break;
			}
		}
	}

}
