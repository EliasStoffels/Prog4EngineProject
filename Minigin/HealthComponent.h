#pragma once
#include "CppBehaviour.h"

namespace dae
{
	class HealthComponent : public CppBehaviour
	{
		friend class GameObject;

	public:
		void Die();
		float GetCurrentHealth() { return m_CurrentHealth; }

		bool TakeDamage(float amount);
		bool DealDamage(HealthComponent* target, float amount);

		virtual ~HealthComponent() = default;
		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) = delete;
		HealthComponent& operator=(const HealthComponent& other) = delete;
		HealthComponent& operator=(HealthComponent&& other) = delete;

	private:
		HealthComponent(float health, int lives, bool autoRespawn = true);
		const float MAX_HEALTH;
		const int MAX_LIVES;
		float m_CurrentHealth = MAX_HEALTH;
		int m_CurrentLives = MAX_LIVES;
		bool m_AutoRespawn;
	};
}

