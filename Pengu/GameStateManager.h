#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"
#include <functional>

namespace dae
{
	class GameStateManager final : public Singleton<GameStateManager>
	{
	public:
		bool playersDead = false;
		int currentGameModeIdx = 0;
	private:
		friend class Singleton<GameStateManager>;
		GameStateManager() = default;
	};
}

