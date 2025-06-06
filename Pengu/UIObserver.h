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
		virtual void Notify(const Event& event, GameObject* object);

		virtual ~UIObserverComponent() = default;
		UIObserverComponent(const UIObserverComponent& other) = delete;
		UIObserverComponent(UIObserverComponent&& other) = delete;
		UIObserverComponent& operator=(const UIObserverComponent& other) = delete;
		UIObserverComponent& operator=(UIObserverComponent&& other) = delete;

	private:
		UIObserverComponent();
		UIObserverComponent(TextureComponent* livesTexture, TextComponent* pointsText);
		int m_CharacterHealth = 3;
		TextureComponent* m_TextureLives = nullptr;
		TextComponent* m_TextPoints = nullptr;
		int m_SnobeeEggs = 6;
		int m_Score = 0;
	};
}



