#include "MuteSoundCommand.h"
#include "ServiceLocator.h"
#include <MixerSoundSystem.h>
#include "iostream"

void dae::MuteSoundCommand::Execute()
{
	if (m_buttonState.ReleasedThisFrame)
	{
		if (m_Muted)
			dae::ServiceLocator::GetInstance().GetSoundSystem().Mute();
		else
			dae::ServiceLocator::GetInstance().GetSoundSystem().UnMute(10.f);

		std::cout << "hello\n";
		m_Muted = !m_Muted;
	}
}
