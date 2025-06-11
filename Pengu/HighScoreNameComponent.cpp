#include "HighScoreNameComponent.h"
#include <GameObject.h>
#include <ResourceManager.h>
#include "TextComponent.h"

namespace dae
{
	void HighScoreNameComponent::ChangeLetter(int idx, bool increase)
	{
		if (increase)
		{
			++m_Name[idx];
			if(m_Name[idx] > 'Z')
				m_Name[idx] = 'A';
		}
		else
		{
			--m_Name[idx];
			if (m_Name[idx] < 'A')
				m_Name[idx] = 'Z';
		}

		m_NameTexture->SetText(std::string{ m_Name });
	}

	HighScoreNameComponent::HighScoreNameComponent(GameObject* owner) : CppBehaviour{owner}
	{
		auto font = dae::ResourceManager::GetInstance().LoadFont("Pengo-Atari 5200.ttf", 25);
		m_NameTexture = GetOwner()->AddComponent<TextComponent>(font);
		m_NameTexture->SetText(std::string{ m_Name });
	}
}