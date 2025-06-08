#pragma once
#include "CppBehaviour.h"
#include "BaseObserver.h"

namespace dae
{
	class TextComponent;
	class TextureComponent;
	class UIObserverComponent : public CppBehaviour, public Observer
	{
		friend class GameObject;

	public:
		void Start() override;
		void Update(float deltaTime) override;
		void Notify(const Event& event, GameObject* object) override;

		virtual ~UIObserverComponent() = default;
		UIObserverComponent(const UIObserverComponent& other) = delete;
		UIObserverComponent(UIObserverComponent&& other) = delete;
		UIObserverComponent& operator=(const UIObserverComponent& other) = delete;
		UIObserverComponent& operator=(UIObserverComponent&& other) = delete;

	private:
		UIObserverComponent(GameObject* owner);
		int m_CharacterHealth = 3;
		TextureComponent* m_TextureEggs = nullptr;
		TextureComponent* m_TextureLives = nullptr;
		TextureComponent* m_TextureBlack = nullptr;
		TextComponent* m_TextPoints = nullptr;
		TextComponent* m_TextRespawn = nullptr;
		int m_SnobeeEggs = 6;
		int m_Score = 0;
		bool m_PlayersDied = false;
		float m_BlackScreenHeight = 0.f;
		float m_TotalDT = 0.f;
		const float BLACK_SCREEN_DELAY = 1.5f;
	};
}



