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
		virtual void PlayLooping(const sound_id id, const float volume, int loops) = 0;
		virtual void Stop(const sound_id id) = 0;
		virtual void StopAllSounds() = 0;
		virtual void LoadSound(const sound_id id, const std::string& filePath) = 0;
		virtual void LoadMusic(const sound_id id, const std::string& filePath) = 0;
		virtual bool IsSoundPlaying(const sound_id id) = 0;
		virtual void Mute() = 0;
		virtual void UnMute(const float volume) = 0;
	};

	class NullSoundSystem final : public SoundSystem
	{
	public:
		NullSoundSystem() = default;
		~NullSoundSystem() override = default;

		void Play(const sound_id, const float ) override {}
		void PlayLooping(const sound_id , const float , int ) override {}
		void Stop(const sound_id ) override {}
		void StopAllSounds() override {}
		void LoadSound(const sound_id , const std::string& ) override {}
		void LoadMusic(const sound_id , const std::string& ) override {}
		bool IsSoundPlaying(const sound_id ) override { return false; }
		void Mute() override {};
		void UnMute(const float) override {};
	};
}
