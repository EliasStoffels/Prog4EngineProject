#include "FpsComponent.h"
#include "GameObject.h"
#include "TextComponent.h"

dae::FpsComponent::FpsComponent()
{
}

void dae::FpsComponent::Start()
{
	m_TextComp = m_OwningGameObject->GetComponent<dae::TextComponent>();
}

void dae::FpsComponent::Update(float deltaTime)
{
	m_totalDeltaTime += deltaTime;

	if(m_totalDeltaTime > m_fpsUpdateDelay)
	{
		float fps = 1 / deltaTime;
		if (m_TextComp)
		{
			m_TextComp->SetText(std::to_string(fps) + " FPS");
		}
		m_totalDeltaTime -= m_fpsUpdateDelay;
	}
}


