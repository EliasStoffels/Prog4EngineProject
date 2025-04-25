#include "MixerSoundSystem.h"
#include <SDL_mixer.h>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <unordered_map>
#include <atomic>

namespace dae
{
	/*class MixerSoundSystem::Impl
	{
	public:
		void Play(const sound_id id, const float volume = 128);
		void Stop(const sound_id id);
		void StopAllSounds();
		void LoadSound(const sound_id id, const std::string& filePath);
		bool IsSoundPlaying(const sound_id id);
	private:

	};

	void MixerSoundSystem::Impl::Play(const sound_id id, const float volume)
	{

	}

	void MixerSoundSystem::Impl::Stop(const sound_id id)
	{
	}

	void MixerSoundSystem::Impl::StopAllSounds()
	{
	}

	void MixerSoundSystem::Impl::LoadSound(const sound_id id, const std::string& filePath)
	{
	}

	bool MixerSoundSystem::Impl::IsSoundPlaying(const sound_id id)
	{
		return false;
	}*/

    class MixerSoundSystem::Impl
    {
    public:
        Impl() : m_ThreadRunning(true), m_WorkerThread(&Impl::ProcessEvents, this)
        {
            Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_FLAC | MIX_INIT_MOD);
            Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
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
            m_EventQueue.push({ SoundEventType::PLAY, id, volume, "" });
            m_Condition.notify_one();
        }

        void Stop(const sound_id id)
        {
            std::lock_guard<std::mutex> lock(m_QueueMutex);
            m_EventQueue.push({ SoundEventType::STOP, id, 0, "" });
            m_Condition.notify_one();
        }

        void StopAllSounds()
        {
            std::lock_guard<std::mutex> lock(m_QueueMutex);
            m_EventQueue.push({ SoundEventType::STOP_ALL, 0, 0, "" });
            m_Condition.notify_one();
        }

        void LoadSound(const sound_id id, const std::string& filePath)
        {
            std::lock_guard<std::mutex> lock(m_QueueMutex);
            m_EventQueue.push({ SoundEventType::LOAD, id, 0, filePath });
            m_Condition.notify_one();
        }

        bool IsSoundPlaying(const sound_id id)
        {
            std::lock_guard<std::mutex> lock(m_PlayingChannelsMutex);
            return m_PlayingChannels.find(id) != m_PlayingChannels.end();
        }

    private:
        enum class SoundEventType { PLAY, STOP, STOP_ALL, LOAD };

        struct SoundEvent {
            SoundEventType type;
            sound_id id;
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
            Mix_Chunk* chunk = Mix_LoadWAV(event.filePath.c_str());
            if (chunk)
            {
                m_SoundChunks[event.id] = chunk;
            }
        }

        std::queue<SoundEvent> m_EventQueue;
        std::mutex m_QueueMutex;
        std::condition_variable m_Condition;

        std::unordered_map<sound_id, Mix_Chunk*> m_SoundChunks;

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

	bool MixerSoundSystem::IsSoundPlaying(const sound_id id)
	{
		return m_Impl->IsSoundPlaying(id);
	}
}

