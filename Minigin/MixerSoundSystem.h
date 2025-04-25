#pragma once
#include "SoundSystem.h"
#include <memory>
#include "string"

namespace dae
{
    class MixerSoundSystem : public SoundSystem
    {
    public:
        MixerSoundSystem();
        ~MixerSoundSystem() override;

        void Play(const sound_id id, const float volume = 128) override;
        void Stop(const sound_id id) override;
        void StopAllSounds() override;
        void LoadSound(const sound_id id, const std::string& filePath) override;
        bool IsSoundPlaying(const sound_id id) override;

    private:
        class Impl;
        std::unique_ptr<Impl> m_Impl;
    };
}

