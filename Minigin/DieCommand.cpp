#include "DieCommand.h"
#include <MixerSoundSystem.h>
#include <ServiceLocator.h>

namespace dae
{
	DieCommand::DieCommand(GameObject* gameObject) : GameObjectCommand{ gameObject }
	{
		m_HealthComponent = gameObject->GetComponent<HealthComponent>();
	}

	void DieCommand::Execute()
	{
		if (m_buttonState.ReleasedThisFrame)
		{
			m_HealthComponent->TakeDamage(100.f);

			dae::ServiceLocator::GetInstance().GetSoundSystem().LoadSound(static_cast<dae::sound_id>(dae::make_sdbm_hash("DieSFX")), "../Data/PengoSoundFX/Touch_Snow-Bee.mp3");
			dae::ServiceLocator::GetInstance().GetSoundSystem().Play(static_cast<dae::sound_id>(dae::make_sdbm_hash("DieSFX")), 50.f);
		}
			
	}
}
