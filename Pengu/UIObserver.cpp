#include "UiObserver.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "EventArgs.h"
#include "TextureComponent.h"
#include <iostream>
#include "GameStateManager.h"
#include "ResourceManager.h"

namespace dae
{
	UIObserverComponent::UIObserverComponent(GameObject* owner) :CppBehaviour{ owner }
	{
		m_TextureLives = owner->AddComponent<dae::TextureComponent>();
		m_TextureLives->SetTexture("Misc.png");
		m_TextureLives->SetWidthAndHeight(48, 48);
		m_TextureLives->SetSourceRect(0, 150, 16, 16);
		m_TextureLives->SetRepeats(GameStateManager::GetInstance().GetLives());
		m_TextureLives->SetRepeatOfsett(glm::vec3{ 50,0,0 });
		m_TextureLives->SetRenderOfsett(glm::vec3{ 20,30,0 });

		m_TextureEggs = owner->AddComponent<dae::TextureComponent>();
		m_TextureEggs->SetTexture("Misc.png");
		m_TextureEggs->SetWidthAndHeight(18, 18);
		m_TextureEggs->SetSourceRect(80, 82, 8, 8);
		m_TextureEggs->SetRepeats(6);
		m_TextureEggs->SetRepeatOfsett(glm::vec3{ -20,0,0 });
		m_TextureEggs->SetRenderOfsett(glm::vec3{ 400,60,0 });

		m_TextureBlack = owner->AddComponent<TextureComponent>();
		m_TextureBlack->SetTexture("BlackBG.png");
		m_TextureBlack->SetWidthAndHeight(672, 0);
		m_TextureBlack->SetSourceRect(100, 100, 10, 10);
		m_TextureBlack->SetRenderOfsett(glm::vec3{ 0,82,0 });
		m_TextureBlack->IsActive(false);

		auto font = dae::ResourceManager::GetInstance().LoadFont("Pengo-Atari 5200.ttf", 20);
		m_TextPoints = owner->AddComponent<dae::TextComponent>(font);
		m_TextPoints->SetRenderOfSet(glm::vec3{ 220,2,0 });

		m_TextRespawn = owner->AddComponent<dae::TextComponent>(font);
		m_TextRespawn->SetText("Player 1 Ready");
		m_TextRespawn->SetRenderOfSet(glm::vec3{ 200,389,0 });
		m_TextRespawn->SetActive(false);
	}

	void UIObserverComponent::Start()
	{
		m_TextPoints->SetText(std::to_string(GameStateManager::GetInstance().GetScore()));
	}

	void UIObserverComponent::Update(float deltaTime)
	{
		m_TotalDT += deltaTime;
		if (m_PlayersDied)
		{
			if (m_TotalDT > BLACK_SCREEN_DELAY)
			{
				m_BlackScreenHeight += deltaTime * 600;
				m_TextureBlack->SetWidthAndHeight(672, m_BlackScreenHeight);

			}
			if (m_BlackScreenHeight > 800)
			{
				m_TextRespawn->SetActive(true);
				GameStateManager::GetInstance().playersDead = true;
			}
		}
		else
		{
			m_BlackScreenHeight -= deltaTime * 600;
			m_TextureBlack->SetWidthAndHeight(672, m_BlackScreenHeight);
			if (m_BlackScreenHeight <= 0.f)
			{
				GameStateManager::GetInstance().playersDead = false;
			}
		}
	}

	void UIObserverComponent::Notify(const Event& event, GameObject*)
	{
		if (event.id == make_sdbm_hash("SnobeeHatched"))
		{
			--m_SnobeeEggs;
			m_TextureEggs->SetRepeats(m_SnobeeEggs);
		}
		else if (event.id == make_sdbm_hash("ScoreChanged"))
		{
			ScoreChangedArgs* args = reinterpret_cast<ScoreChangedArgs*>(event.arg);
			m_Score += args->amount;
			m_TextPoints->SetText(std::to_string(m_Score));
			m_TextPoints->SetRenderOfSet(glm::vec3{ 210 - m_TextPoints->GetSize().x , 2, 0 });
		}
		else if (event.id == make_sdbm_hash("PengoDied"))
		{
			m_BlackScreenHeight = 0.f;
			m_TextureBlack->IsActive(true);
			m_PlayersDied = true;
			m_TextureLives->SetSourceRect(36, 150, 16, 16);
		}
		else if (event.id == make_sdbm_hash("Respawn"))
		{
			m_BlackScreenHeight = 800.f;
			m_PlayersDied = false;
			m_TextRespawn->SetActive(false);
			m_TextureLives->SetRepeats(GameStateManager::GetInstance().GetLives());
			m_TextureLives->SetSourceRect(0, 150, 16, 16);
		}
	}
}
