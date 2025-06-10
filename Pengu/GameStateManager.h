#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"
#include <functional>
#include "BaseObserver.h"
#include <chrono>

namespace dae
{
	class GameStateManager final : public Singleton<GameStateManager>, public Observer
	{
	public:
		bool playersDead = false;
		int currentGameModeIdx = 0;
		void Notify(const Event& event, GameObject* gameObject) override;
		int GetLives() { return m_Lives; }
		int GetScore() { return m_Score; }
		float GetLevelTime() { return m_LevelTime; }
		void StartLevel();

	private:
		friend class Singleton<GameStateManager>;
		GameStateManager() = default;
		int m_Score = 0;
		int m_Lives = 3;
		int m_HighScores[5]{};
		std::chrono::high_resolution_clock::time_point m_LevelStartTime{};
		float m_LevelTime = 0.f;

	};
}

