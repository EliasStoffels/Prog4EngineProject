#include "UiObserver.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "EventArgs.h"

namespace dae
{
	UIObserverComponent::UIObserverComponent() :m_CharacterHealth{ 3 }
	{

	}

	UIObserverComponent::UIObserverComponent(TextComponent* livesText, TextComponent* pointsText) :m_CharacterHealth{ 3 }, m_TextLives{livesText}, m_TextPoints{pointsText}
	{
	}

	void UIObserverComponent::Start()
	{
		m_TextLives->SetText("# Lives: " + std::to_string(m_CharacterHealth));
		m_TextPoints->SetText("score: 0");
	}

	void UIObserverComponent::Notify(const Event& event, GameObject*)
	{
		if (event.id == make_sdbm_hash("CharacterDied") && m_CharacterHealth > 0)
		{
			--m_CharacterHealth;
			m_TextLives->SetText("# Lives: " + std::to_string(m_CharacterHealth));
		}
		else if (event.id == make_sdbm_hash("ScoreChanged"))
		{
			ScoreChangedArgs* args = reinterpret_cast<ScoreChangedArgs*>(event.arg);
			m_Score += args->amount;
			m_TextPoints->SetText("score: " + std::to_string(m_Score));
		}
	}
}
