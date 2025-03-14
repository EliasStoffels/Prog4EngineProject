#include "HealthComponent.h"
#include "GameObject.h"
#include "iostream"
namespace dae
{
	void HealthComponent::Die()
	{
		--m_CurrentHealth;
		m_OwningGameObject->NotifyObservers(Event{ sdbm_hash("CharacterDied") });
	}

	HealthComponent::HealthComponent(int health) :MAX_HEALTH{health}
	{
		m_CurrentHealth = MAX_HEALTH;
	}
}
