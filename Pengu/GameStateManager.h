#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"
#include "BaseObserver.h"
#include <chrono>

namespace dae
{
	struct HighScore
	{
		int score = 0;
		int round = 0;
		char name[4] = "AAA";
	};

	class GameStateManager final : public Singleton<GameStateManager>, public Observer
	{
	public:
		bool playersDead = false;
		int currentGameModeIdx = 0;
		void Notify(const Event& event, GameObject* gameObject) override;
		int GetLevel() { return m_CurrentLevel; }
		int GetLives() { return m_Lives; }
		int GetScore() { return m_Score; }
		int GetHighScoreIndex() { return m_NewHighscoreIdx; }
		std::vector<HighScore> GetHighScores() { return m_HighScores; };
		float GetLevelTime() { return m_LevelTime; }
		void StartLevel();
		void SetHighScoreName(const std::string& name);
		void Reset();

	private:
		friend class Singleton<GameStateManager>;
		GameStateManager();
		~GameStateManager();
		int m_CurrentLevel = 0;
		int m_Score = 0;
		int m_Lives = 3;
		std::vector<HighScore> m_HighScores = std::vector<HighScore>(5);
		std::chrono::high_resolution_clock::time_point m_LevelStartTime{};
		float m_LevelTime = 0.f;
		int m_NewHighscoreIdx = -1;
	};
}

