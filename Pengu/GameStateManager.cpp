#include "GameStateManager.h"
#include "EventArgs.h"
#include "SceneManager.h"
#include <iostream>

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
		auto levelEndTime = std::chrono::high_resolution_clock::now();
		auto deltaTime = std::chrono::duration_cast<std::chrono::seconds>(levelEndTime - m_LevelStartTime);

		float timeInSeconds = static_cast<float>(deltaTime.count());

		if (timeInSeconds <= 19)
		{
			m_Score += 5000;
		}
		else if (timeInSeconds <= 29)
		{
			m_Score += 2000;
		}
		else if (timeInSeconds <= 39)
		{
			m_Score += 1000;
		}
		else if (timeInSeconds <= 49)
		{
			m_Score += 500;
		}
		else if (timeInSeconds <= 59)
		{
			m_Score += 10;
		}

		for (int score : m_HighScores)
		{
			score;
;		}

		SceneManager::GetInstance().LoadScene("ScoreScene");
	}
	else if (event.id == make_sdbm_hash("ScoreChanged"))
	{
		ScoreChangedArgs* args = reinterpret_cast<ScoreChangedArgs*>(event.arg);
		m_Score += args->amount;
	}
}

void dae::GameStateManager::StartLevel()
{
	m_LevelStartTime = std::chrono::high_resolution_clock::now();
}
