#include "LoadSceneCommand.h"
#include <SceneManager.h>

dae::LoadSceneCommand::LoadSceneCommand(const std::string& sceneName) : m_Scene{sceneName}
{
}

void dae::LoadSceneCommand::Execute()
{
	if (m_buttonState.ReleasedThisFrame)
		SceneManager::GetInstance().LoadScene(m_Scene);
}
