#include "EnemyComponent.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include <iostream>

namespace dae
{
	EnemyComponent::EnemyComponent(float speed, GridComponent* grid)
		: m_Speed{ speed }, m_GridPtr{ grid }, m_TexturePtr{ nullptr }
	{
		m_CurrentState = std::make_unique<EnemySpawningState>();
	}

	void EnemyComponent::Start()
	{
		m_TexturePtr = m_OwningGameObject->GetComponent<TextureComponent>();
		m_CurrentState->Enter(this);
	}

	void EnemyComponent::Update(float deltaTime)
	{
		auto newState = m_CurrentState->Update(this, deltaTime);
		if (newState)
			ChangeState(std::move(newState));
	}
	void EnemyComponent::Move(const glm::vec3& direction)
	{
		m_Direction = direction;
		auto newState = m_CurrentState->OnMove(this);
		if (newState)
			ChangeState(std::move(newState));
	}
	void EnemyComponent::Break()
	{
		auto newState = m_CurrentState->Break(this);
		if (newState)
			ChangeState(std::move(newState));
	}
	void EnemyComponent::GetHit(GameObject* block)
	{
		auto newState = m_CurrentState->GetHit(this, block);
		if (newState)
			ChangeState(std::move(newState));
	}
	void EnemyComponent::ChangeState(std::unique_ptr<EnemyState> newState)
	{
		m_CurrentState->Exit(this);
		m_CurrentState = std::move(newState);
		m_CurrentState->Enter(this);
	}
}
