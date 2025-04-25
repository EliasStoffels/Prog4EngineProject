#pragma once
#include "Singleton.h"
#include <memory>
#include "SoundSystem.h"

namespace dae
{
	class ServiceLocator final : public Singleton<ServiceLocator>
	{
		static std::unique_ptr<SoundSystem> _ss_instance;
	public:
		static SoundSystem& GetSoundSystem() { return *_ss_instance; }
		static void RegisterSoundSystem(std::unique_ptr<SoundSystem>& ss) {
			_ss_instance = std::move(ss);

		};
	};
}
