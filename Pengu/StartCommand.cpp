#include "StartCommand.h"
#include "SceneManager.h"

namespace dae
{
	StartCommand::StartCommand()
	{

	}

	void dae::StartCommand::Execute()
	{
		if(m_buttonState.ReleasedThisFrame)
			dae::SceneManager::GetInstance().LoadScene("Pengo");
	}

}
