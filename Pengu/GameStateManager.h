#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"
#include <functional>
#include "BaseObserver.h"

namespace dae
{
	class GameStateManager final : public Singleton<GameStateManager>, public Observer
	{
	public:
		bool playersDead = false;
		int currentGameModeIdx = 0;
		void Notify(const Event& event, GameObject* gameObject) override;

	private:
		friend class Singleton<GameStateManager>;
		GameStateManager() = default;
		int m_Lives = 3;
	};
}

