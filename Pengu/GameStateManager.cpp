#include "GameStateManager.h"
#include "EventArgs.h"
#include "SceneManager.h"

void dae::GameStateManager::Notify(const Event& event, GameObject* )
{
	if (event.id == make_sdbm_hash("PengoDied"))
	{
		--m_Lives;
		if (m_Lives <= 0)
		{
			SceneManager::GetInstance().LoadScene("ScoreScene");
		}
	}
	if (event.id == make_sdbm_hash("LevelWon"))
	{
		SceneManager::GetInstance().LoadScene("ScoreScene");
	}
	else if (event.id == make_sdbm_hash("ScoreChanged"))
	{
		ScoreChangedArgs* args = reinterpret_cast<ScoreChangedArgs*>(event.arg);
		m_Score += args->amount;
	}
}
