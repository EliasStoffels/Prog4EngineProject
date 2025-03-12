#pragma once
#include "Singleton.h"

namespace dae
{
	class TimeSingleton : public Singleton<TimeSingleton>
	{
		TimeSingleton();
		~TimeSingleton();
		friend class Singleton<TimeSingleton>;

		float m_deltaTime = 0;
	public:
		void SetDeltaTime(float deltaTime) { m_deltaTime = deltaTime; }
		float GetDeltaTime() { return m_deltaTime; }
	};
}

