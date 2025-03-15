#pragma once
#include "CppBehaviour.h"
#include "BaseObserver.h"

namespace dae
{
	class TextComponent;
	class UiObserverComponent : public CppBehaviour, public Observer
	{
		friend class GameObject;

	public:
		void Start() override;
		virtual void Notify(const Event& event, GameObject* object);

		virtual ~UiObserverComponent() = default;
		UiObserverComponent(const UiObserverComponent& other) = delete;
		UiObserverComponent(UiObserverComponent&& other) = delete;
		UiObserverComponent& operator=(const UiObserverComponent& other) = delete;
		UiObserverComponent& operator=(UiObserverComponent&& other) = delete;

	private:
		UiObserverComponent();
		UiObserverComponent(TextComponent* livesText,TextComponent* pointsText);
		int m_CharacterHealth;
		TextComponent* m_TextLives = nullptr;
		TextComponent* m_TextPoints = nullptr;
	};
}



