#pragma once
#include "SoundSystem.h"
#include <iostream>

namespace dae {
    class LoggingSoundSystem : public SoundSystem {
    public:
        LoggingSoundSystem(std::unique_ptr<SoundSystem>&& soundSystem){
            m_WrappedSoundSystem = std::move(soundSystem);
        }

        void Play(const sound_id id, const float volume);
        void PlayLooping(const sound_id id, const float volume, int loops);
        void Stop(const sound_id id);
        void StopAllSounds();
        void LoadSound(const sound_id id, const std::string& filePath);
        void LoadMusic(const sound_id id, const std::string& filePath);
        bool IsSoundPlaying(const sound_id id);

    private:
        std::unique_ptr<SoundSystem> m_WrappedSoundSystem = nullptr;
    };
}

