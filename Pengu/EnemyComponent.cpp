#include "EnemyComponent.h"

namespace dae
{
	void EnemyComponent::Start()
	{
	}

	void EnemyComponent::Update(float )
	{

	}
	void EnemyComponent::ChangeState(std::unique_ptr<EnemyState> newState)
	{
		m_CurrentState->Exit(this);
		m_CurrentState = std::move(newState);
		m_CurrentState->Enter(this);
	}
}
