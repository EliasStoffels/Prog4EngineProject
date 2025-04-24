#include "HealthComponent.h"
#include "GameObject.h"
#include "iostream"

namespace dae
{
	void HealthComponent::Die()
	{
		--m_CurrentLives;
		m_OwningGameObject->NotifyObservers(Event{ make_sdbm_hash("CharacterDied") });
		if (m_CurrentLives > 0)
		{
			m_CurrentHealth = MAX_HEALTH;
		}
	}

	bool HealthComponent::TakeDamage(float amount)
	{
		m_CurrentHealth -= amount;

		if (m_CurrentHealth <= 0)
		{
			Die();
			return true;
		}
		return false;
	}

	bool HealthComponent::DealDamage(HealthComponent* target, float amount)
	{
		if (target->TakeDamage(amount))
		{
			return true;
		}
		return false;
	}

	HealthComponent::HealthComponent(float health, int lives, bool autoRespawn) :MAX_HEALTH{ health }, MAX_LIVES{lives},m_AutoRespawn{autoRespawn}
	{
		m_CurrentHealth = MAX_HEALTH;
		m_CurrentLives = MAX_LIVES;
	}
}
