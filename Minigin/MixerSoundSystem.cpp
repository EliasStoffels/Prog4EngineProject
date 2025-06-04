#include "MixerSoundSystem.h"
#include <SDL_mixer.h>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <unordered_map>
#include <atomic>
#include <iostream>

namespace dae
{
    class MixerSoundSystem::Impl
    {
    public:
        Impl() : m_ThreadRunning(true), m_WorkerThread(&Impl::ProcessEvents, this)
        {
            Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_FLAC | MIX_INIT_MOD);
            Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
            Mix_AllocateChannels(32);
        }

        ~Impl()
        {
            m_ThreadRunning = false;
            m_Condition.notify_one();
            m_WorkerThread.join();

            for (auto& pair : m_SoundChunks) {
                Mix_FreeChunk(pair.second);
            }
            Mix_CloseAudio();
            Mix_Quit();
        }

        void Play(const sound_id id, const float volume = 128)
        {
            std::lock_guard<std::mutex> lock(m_QueueMutex);
            m_EventQueue.push({ SoundEventType::PLAY, id, 1, volume, "" });
            m_Condition.notify_one();
        }

        void Stop(const sound_id id)
        {
            std::lock_guard<std::mutex> lock(m_QueueMutex);
            m_EventQueue.push({ SoundEventType::STOP, id, 1, 0, "" });
            m_Condition.notify_one();
        }

        void StopAllSounds()
        {
            std::lock_guard<std::mutex> lock(m_QueueMutex);
            m_EventQueue.push({ SoundEventType::STOP_ALL, 0, 1, 0, "" });
            m_Condition.notify_one();
        }

        void LoadSound(const sound_id id, const std::string& filePath)
        {
            std::lock_guard<std::mutex> lock(m_QueueMutex);
            m_EventQueue.push({ SoundEventType::LOAD, id, 1, 0, filePath });
            m_Condition.notify_one();
        }

        void LoadMusic(const sound_id id, const std::string& filePath)
        {
            std::lock_guard<std::mutex> lock(m_QueueMutex);
            m_EventQueue.push({ SoundEventType::LOAD_MUSIC, id, 1, 0, filePath });
            m_Condition.notify_one();
        }

        bool IsSoundPlaying(const sound_id id)
        {
            std::lock_guard<std::mutex> lock(m_PlayingChannelsMutex);
            return m_PlayingChannels.find(id) != m_PlayingChannels.end();
        }

        void PlayLooping(const sound_id id, const float volume = 128, int loops = -1)
        {
            std::lock_guard<std::mutex> lock(m_QueueMutex);
            m_EventQueue.push({ SoundEventType::LOOP, id, loops, volume, "" });
            m_Condition.notify_one();
        }

    private:
        enum class SoundEventType { PLAY, STOP, STOP_ALL, LOAD, LOAD_MUSIC, LOOP };

        struct SoundEvent {
            SoundEventType type;
            sound_id id;
            int loops;
            float volume;
            std::string filePath;
        };

        void ProcessEvents()
        {
            while (m_ThreadRunning)
            {
                std::unique_lock<std::mutex> lock(m_QueueMutex);
                m_Condition.wait(lock, [this]() {
                    return !m_EventQueue.empty() || !m_ThreadRunning;
                    });

                if (!m_ThreadRunning) break;

                SoundEvent event = m_EventQueue.front();
                m_EventQueue.pop();
                lock.unlock();

                switch (event.type)
                {
                case SoundEventType::PLAY:
                    HandlePlayEvent(event);
                    break;
                case SoundEventType::STOP:
                    HandleStopEvent(event);
                    break;
                case SoundEventType::STOP_ALL:
                    HandleStopAllEvent();
                    break;
                case SoundEventType::LOAD:
                    HandleLoadEvent(event);
                    break;
                case SoundEventType::LOAD_MUSIC:
                    HandleLoadMusicEvent(event);
                    break;
                case SoundEventType::LOOP:
                    HandleLoopEvent(event);
                    break;

                }
            }
        }

        void HandlePlayEvent(const SoundEvent& event)
        {
            auto it = m_SoundChunks.find(event.id);
            if (it != m_SoundChunks.end())
            {
                int channel = Mix_PlayChannel(-1, it->second, 0);
                if (channel != -1)
                {
                    Mix_Volume(channel, static_cast<int>(event.volume));

                    std::lock_guard<std::mutex> lock(m_PlayingChannelsMutex);
                    m_PlayingChannels[event.id] = channel;
                }
            }

            auto it2 = m_SoundMusic.find(event.id);
            if (it2 != m_SoundMusic.end())
            {
                int channel = Mix_PlayMusic(it2->second, event.loops);
                if (channel != -1)
                {
                    Mix_VolumeMusic(static_cast<int>(event.volume));

                    std::lock_guard<std::mutex> lock(m_PlayingChannelsMutex);
                    m_PlayingChannels[event.id] = channel;
                }
            }
        }

        void HandleStopEvent(const SoundEvent& event)
        {
            std::lock_guard<std::mutex> lock(m_PlayingChannelsMutex);
            auto it = m_PlayingChannels.find(event.id);
            if (it != m_PlayingChannels.end())
            {
                Mix_HaltChannel(it->second);
                m_PlayingChannels.erase(it);
            }
        }

        void HandleStopAllEvent()
        {
            std::lock_guard<std::mutex> lock(m_PlayingChannelsMutex);
            Mix_HaltChannel(-1);
            m_PlayingChannels.clear();
        }

        void HandleLoadEvent(const SoundEvent& event)
        {
            auto it = m_SoundChunks.find(event.id);
            if (it != m_SoundChunks.end())
            {
                return;
            }

            Mix_Chunk* chunk = Mix_LoadWAV(event.filePath.c_str());
            if (chunk)
            {
                m_SoundChunks[event.id] = chunk;
            }
        }

        void HandleLoadMusicEvent(const SoundEvent& event)
        {
            auto it = m_SoundMusic.find(event.id);
            if (it != m_SoundMusic.end())
            {
                return;
            }

            Mix_Music* chunk = Mix_LoadMUS(event.filePath.c_str());
            if (chunk)
            {
                m_SoundMusic[event.id] = chunk;
            }
        }

        void HandleLoopEvent(const SoundEvent& event)
        {
            auto it = m_SoundChunks.find(event.id);
            if (it != m_SoundChunks.end())
            {
                // Use channel 0 for music (reserved)
                int channel = Mix_PlayChannel(0, it->second, event.loops);
                if (channel != -1)
                {
                    Mix_Volume(channel, static_cast<int>(event.volume));
                    std::lock_guard<std::mutex> lock(m_PlayingChannelsMutex);
                    m_PlayingChannels[event.id] = channel;
                }
                else
                {
                    std::cerr << "Mix_PlayChannel error: " << Mix_GetError() << std::endl;
                }
            }

            auto it2 = m_SoundMusic.find(event.id);
            if (it2 != m_SoundMusic.end())
            {
                int channel = Mix_PlayMusic(it2->second, event.loops);
                if (channel != -1)
                {
                    Mix_VolumeMusic(static_cast<int>(event.volume));
                    std::lock_guard<std::mutex> lock(m_PlayingChannelsMutex);
                    m_PlayingChannels[event.id] = channel;
                }
                else
                {
                    std::cerr << "Mix_PlayChannel error: " << Mix_GetError() << std::endl;
                }
            }
        }

        std::queue<SoundEvent> m_EventQueue;
        std::mutex m_QueueMutex;
        std::condition_variable m_Condition;

        std::unordered_map<sound_id, Mix_Chunk*> m_SoundChunks;
        std::unordered_map<sound_id, Mix_Music*> m_SoundMusic;

        std::unordered_map<sound_id, int> m_PlayingChannels;
        std::mutex m_PlayingChannelsMutex;

        std::atomic<bool> m_ThreadRunning{ false };
        std::thread m_WorkerThread;
    };

	MixerSoundSystem::MixerSoundSystem() : m_Impl(std::make_unique<Impl>()) {}
	MixerSoundSystem::~MixerSoundSystem() = default;

	void MixerSoundSystem::Play(const sound_id id, const float volume)
	{
		m_Impl->Play(id, volume);
	}

    void MixerSoundSystem::PlayLooping(const sound_id id, const float volume, int loops)
    {
        m_Impl->PlayLooping(id, volume, loops);
    }

	void MixerSoundSystem::Stop(const sound_id id)
	{
		m_Impl->Stop(id);
	}

	void MixerSoundSystem::StopAllSounds()
	{
		m_Impl->StopAllSounds();
	}

	void MixerSoundSystem::LoadSound(const sound_id id, const std::string& filePath)
	{
		m_Impl->LoadSound(id, filePath);
	}

    void MixerSoundSystem::LoadMusic(const sound_id id, const std::string& filePath)
    {
        m_Impl->LoadMusic(id, filePath);
    }

	bool MixerSoundSystem::IsSoundPlaying(const sound_id id)
	{
		return m_Impl->IsSoundPlaying(id);
	}
}

