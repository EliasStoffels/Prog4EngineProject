#include "UiObserver.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "EventArgs.h"
#include "TextureComponent.h"

namespace dae
{
	UIObserverComponent::UIObserverComponent(TextureComponent* livesTexture, TextComponent* pointsText) : m_TextureLives{livesTexture}, m_TextPoints{pointsText}
	{
	}

	void UIObserverComponent::Start()
	{
		m_TextPoints->SetText("0");
	}

	void UIObserverComponent::Notify(const Event& event, GameObject*)
	{
		if (event.id == make_sdbm_hash("SnobeeHatched"))
		{
			--m_SnobeeEggs;
			m_TextureLives->SetRepeats(m_SnobeeEggs);
		}
		else if (event.id == make_sdbm_hash("ScoreChanged"))
		{
			ScoreChangedArgs* args = reinterpret_cast<ScoreChangedArgs*>(event.arg);
			m_Score += args->amount;
			m_TextPoints->SetText(std::to_string(m_Score));
			m_TextPoints->SetRenderOfSet(glm::vec3{ 210 - m_TextPoints->GetSize().x , 2, 0 });

		}
	}
}
