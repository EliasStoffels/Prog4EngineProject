#include "FpsComponent.h"
#include "GameObject.h"
#include "TextComponent.h"

dae::FpsComponent::FpsComponent()
{
}

void dae::FpsComponent::Start()
{
	auto texComp = static_cast<dae::TextComponent*>(m_OwningGameObject->GetComponent<dae::TextComponent>());
	if(texComp)
	{
		texComp->SetPosition(0.f, 0.f);
	}
}

void dae::FpsComponent::Update([[maybe_unused]] float deltaTime)
{
	m_totalDeltaTime += deltaTime;

	if(m_totalDeltaTime > m_fpsUpdateDelay)
	{
		float fps = 1 / deltaTime;
		auto texComp = static_cast<dae::TextComponent*>(m_OwningGameObject->GetComponent<dae::TextComponent>());
		if (texComp)
		{
			texComp->SetText(std::to_string(fps) + " FPS");
		}
		m_totalDeltaTime -= m_fpsUpdateDelay;
	}
}


