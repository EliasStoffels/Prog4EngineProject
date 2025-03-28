#include "UiObserver.h"
#include "GameObject.h"
#include "TextComponent.h"
#include <AchievementObserver.h>

namespace dae
{
	UiObserverComponent::UiObserverComponent():m_CharacterHealth{3}
	{
	}

	UiObserverComponent::UiObserverComponent(TextComponent* livesText, TextComponent* pointsText) :m_CharacterHealth{ 3 }
	{
		m_TextLives = livesText;
		m_TextPoints = pointsText;
	}

	void UiObserverComponent::Start()
	{
		m_TextLives->SetText("# Lives: " + std::to_string(m_CharacterHealth));
		m_TextPoints->SetText("score: 0");
	}

	void UiObserverComponent::Notify(const Event& event, GameObject*)
	{
		if (event.id == sdbm_hash("CharacterDied") && m_CharacterHealth > 0)
		{
			--m_CharacterHealth;
			m_TextLives->SetText("# Lives: " + std::to_string(m_CharacterHealth));
		}
		else if (event.id == sdbm_hash("ScoreChanged"))
		{
			m_TextPoints->SetText("score: " + std::to_string(reinterpret_cast<ScoreChangedArgs*>(event.arg)->newScore));
		}
	}
}
