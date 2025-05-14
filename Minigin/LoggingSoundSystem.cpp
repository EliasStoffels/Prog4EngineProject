#include "LoggingSoundSystem.h"

namespace dae
{
    void LoggingSoundSystem::Play(const sound_id id, const float volume = 128)
    {
        std::cout << "called play with id: " << id << " and volume: " << volume << "\n";
        m_WrappedSoundSystem->Play(id, volume);
    }

    void LoggingSoundSystem::PlayLooping(const sound_id id, const float volume, int loops)
    {
        std::cout << "called play looping with id: " << id << " and volume: " << volume << "\n";
        m_WrappedSoundSystem->PlayLooping(id, volume, loops);
    }

    void LoggingSoundSystem::Stop(const sound_id id) 
    {
        std::cout << "called stop with id: " << id << "\n";
        m_WrappedSoundSystem->Stop(id);
    }
    void LoggingSoundSystem::StopAllSounds()
    {
        std::cout << "called stopAllSounds\n";
        m_WrappedSoundSystem->StopAllSounds();
    }
    void LoggingSoundSystem::LoadSound(const sound_id id, const std::string& filePath)
    {
        std::cout << "called LoadSound with id: " << id << " and filePath: " << filePath << "\n";
        m_WrappedSoundSystem->LoadSound(id, filePath);
    }
    void LoggingSoundSystem::LoadMusic(const sound_id id, const std::string& filePath)
    {
        std::cout << "called LoadSound with id: " << id << " and filePath: " << filePath << "\n";
        m_WrappedSoundSystem->LoadMusic(id, filePath);
    }
    bool LoggingSoundSystem::IsSoundPlaying(const sound_id id)
    {
        std::cout << "called IsSoundPlaying with id: " << id << "\n";
        return  m_WrappedSoundSystem->IsSoundPlaying(id);
    }
}

