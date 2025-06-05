#pragma once
#include "CppBehaviour.h"
#include "BaseObserver.h"

namespace dae
{
	class TextComponent;
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
		UIObserverComponent(TextComponent* livesText, TextComponent* pointsText);
		int m_CharacterHealth;
		TextComponent* m_TextLives = nullptr;
		TextComponent* m_TextPoints = nullptr;
	};
}



