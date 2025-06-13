#include "GameStateManager.h"
#include "EventArgs.h"
#include "SceneManager.h"
#include <iostream>
#include <fstream>
#include <iterator>

void dae::GameStateManager::Notify(const Event& event, GameObject* )
{
	if (event.id == make_sdbm_hash("PengoDied"))
	{
		--m_Lives;
		if (m_Lives <= 0)
		{
			auto it = std::find_if(m_HighScores.begin(), m_HighScores.end(), [this](const HighScore& highScore) {return m_Score > highScore.score; });
			if (it != m_HighScores.end())
			{
				m_NewHighscoreIdx = std::distance(m_HighScores.begin(), it);
				m_HighScores.insert(it, HighScore{ m_Score, m_CurrentLevel, "AAA" });
				m_HighScores.pop_back();
				SceneManager::GetInstance().LoadScene("HighScoreScene");
			}
			else 
				SceneManager::GetInstance().LoadScene("Main");
			m_CurrentLevel = 0;
		}
	}
	if (event.id == make_sdbm_hash("LevelWon"))
	{
		auto levelEndTime = std::chrono::high_resolution_clock::now();
		auto deltaTime = std::chrono::duration_cast<std::chrono::seconds>(levelEndTime - m_LevelStartTime);

		m_LevelTime = static_cast<float>(deltaTime.count());

		if (m_LevelTime <= 19)
		{
			m_Score += 5000;
		}
		else if (m_LevelTime <= 29)
		{
			m_Score += 2000;
		}
		else if (m_LevelTime <= 39)
		{
			m_Score += 1000;
		}
		else if (m_LevelTime <= 49)
		{
			m_Score += 500;
		}
		else if (m_LevelTime <= 59)
		{
			m_Score += 10;
		}

		if (m_CurrentLevel >= 2)
		{
			auto it = std::find_if(m_HighScores.begin(), m_HighScores.end(), [this](const HighScore& highScore) {return m_Score > highScore.score; });
			if (it != m_HighScores.end())
			{
				m_NewHighscoreIdx = std::distance(m_HighScores.begin(), it);
				m_HighScores.insert(it, HighScore{ m_Score, m_CurrentLevel, "AAA" });
				m_HighScores.pop_back();
				SceneManager::GetInstance().LoadScene("HighScoreScene");
			}
			else
			{
				SceneManager::GetInstance().LoadScene("Main");
			}
			m_CurrentLevel = 0;
		}
		else
		{
			++m_CurrentLevel;
			SceneManager::GetInstance().LoadScene("ScoreScene");
		}
		
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

void dae::GameStateManager::SetHighScoreName(const std::string& name)
{
	m_HighScores[m_NewHighscoreIdx].name[0] = name.c_str()[0];
	m_HighScores[m_NewHighscoreIdx].name[1] = name.c_str()[1];
	m_HighScores[m_NewHighscoreIdx].name[2] = name.c_str()[2];
}

void dae::GameStateManager::Reset()
{
	m_CurrentLevel = 0;
	m_Score = 0;
	m_Lives = 3;
	m_LevelTime = 0.f;
	m_NewHighscoreIdx = -1;
}

dae::GameStateManager::GameStateManager()
{
	std::ifstream file("../data/HighScores.bin", std::ios::binary);
	if (!file.is_open())
	{
		std::cerr << "Error opening file\n";
		return;
	}

	file.read(reinterpret_cast<char*>(m_HighScores.data()), m_HighScores.size() * sizeof(HighScore));

	file.close();

}

dae::GameStateManager::~GameStateManager()
{
	std::ofstream file("../data/HighScores.bin", std::ios::binary);
	if (!file.is_open())
	{
		std::cerr << "Error opening file\n";
		return;
	}

	file.write(reinterpret_cast<char*>(m_HighScores.data()), m_HighScores.size() * sizeof(HighScore));

	file.close();
}
