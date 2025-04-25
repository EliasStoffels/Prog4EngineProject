#pragma once
#include "Singleton.h"
#include <memory>
#include <string>

namespace dae
{
	using sound_id = unsigned short;
	class SoundSystem
	{
	public:
		virtual ~SoundSystem() = default;
		virtual void Play(const sound_id id, const float volume) = 0;
		virtual void Stop(const sound_id id) = 0;
		virtual void StopAllSounds() = 0;
		virtual void LoadSound(const sound_id id, const std::string& filePath) = 0;
		virtual bool IsSoundPlaying(const sound_id id) = 0;
	};
}
