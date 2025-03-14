#pragma once
#include "CppBehaviour.h"

namespace dae
{
	class HealthComponent : public CppBehaviour
	{
		friend class GameObject;

	public:
		void Die();
		int GetCurrentHealth() { return m_CurrentHealth; }

		virtual ~HealthComponent() = default;
		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) = delete;
		HealthComponent& operator=(const HealthComponent& other) = delete;
		HealthComponent& operator=(HealthComponent&& other) = delete;

	private:
		HealthComponent(int health);
		int MAX_HEALTH;
		int m_CurrentHealth = MAX_HEALTH;
	};
}

