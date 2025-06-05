#include "EnemyState.h"
#include "EnemyComponent.h"
#include "TextureComponent.h"
#include "GameObject.h"
#include "GridComponent.h"
#include <iostream>
#include <algorithm>
#include "TileComponent.h"

namespace dae
{
	// Walking State
	//============================================================================================================================================================================================
	void EnemyWalkingState::Enter(EnemyComponent* snobee)
	{
		m_TexturePtr = snobee->GetTexture();
		m_Direction = snobee->GetDirection();
		if (m_Direction.x < 0)
		{
			m_TexturePtr->SetSourceRect(32, 160);
		}
		if (m_Direction.x > 0)
		{
			m_TexturePtr->SetSourceRect(96, 160);
		}
		if (m_Direction.y < 0)
		{
			m_TexturePtr->SetSourceRect(64, 160);
		}
		if (m_Direction.y > 0)
		{
			m_TexturePtr->SetSourceRect(0, 160);
		}

		m_TargetPosition = snobee->GetOwner()->GetWorldPosition();
	}

	std::unique_ptr<EnemyState> EnemyWalkingState::Update(EnemyComponent* snobee, float deltaTime)
	{
		auto transform = snobee->GetOwner()->GetTransform();
		glm::vec3 direction = (m_TargetPosition - transform->GetWorldPosition());

		//std::cout << transform->GetWorldPosition().x << ", " << transform->GetWorldPosition().y << "\n";

		float sqrLength = glm::dot(direction, direction);
		if (sqrLength < 4)
		{
			transform->SetLocalPosition(m_TargetPosition - transform->GetWorldPosition() + transform->GetLocalPosition());
		}
		else
		{
			float length = std::sqrt(sqrLength);
			direction.x /= length;
			direction.y /= length;

			direction.x *= (snobee->GetSpeed() * deltaTime);
			direction.y *= (snobee->GetSpeed() * deltaTime);

			if (m_TargetPosition.x != FLT_MAX)
				transform->Move(direction);
		}
		Animate(snobee, deltaTime);

		return nullptr;
	}

	void EnemyWalkingState::Animate(EnemyComponent* snobee, float deltaTime)
	{
		m_TotalDT += deltaTime;
		if (m_TotalDT > FRAME_DELAY)
		{
			m_TotalDT -= FRAME_DELAY;

			if (snobee->GetOwner()->GetWorldPosition() != m_TargetPosition && m_TargetPosition.x != FLT_MAX)
				++m_CurrentFrame %= 2;
			else
				m_CurrentFrame = 0;

			int currentFrameOffset = 16 * m_CurrentFrame;

			if (m_Direction.x < 0)
			{
				m_TexturePtr->SetSourceRect(32 + currentFrameOffset, 160);
			}
			if (m_Direction.x > 0)
			{
				m_TexturePtr->SetSourceRect(96 + currentFrameOffset, 160);
			}
			if (m_Direction.y < 0)
			{
				m_TexturePtr->SetSourceRect(64 + currentFrameOffset, 160);
			}
			if (m_Direction.y > 0)
			{
				m_TexturePtr->SetSourceRect(currentFrameOffset, 160);
			}
		}
	}

	void EnemyWalkingState::Exit(EnemyComponent* snobee)
	{
		snobee->GetOwner()->SetLocalPosition(m_TargetPosition - snobee->GetOwner()->GetWorldPosition() + snobee->GetOwner()->GetLocalPosition());
	}

	std::unique_ptr<EnemyState> EnemyWalkingState::OnMove(EnemyComponent* snobee)
	{
		if (m_TargetPosition == snobee->GetOwner()->GetWorldPosition() || m_TargetPosition.x == FLT_MAX)
		{
			m_Direction = snobee->GetDirection();
			auto goTransform = snobee->GetOwner()->GetTransform();
			auto currentPos = goTransform->GetWorldPosition();
			m_TargetPosition = snobee->GetGrid()->RequestMove(currentPos, m_Direction);
		}

		return nullptr;
	}

	std::unique_ptr<EnemyState> EnemyWalkingState::Break(EnemyComponent* snobee)
	{
		if (m_TargetPosition != snobee->GetOwner()->GetWorldPosition() && m_TargetPosition.x != FLT_MAX)
			return nullptr;

		auto blockState = snobee->GetGrid()->RequestBreak(snobee->GetOwner()->GetWorldPosition(), m_Direction);

		if (blockState == BlockState::Breaking)
		{
			return std::make_unique<EnemyBreakingState>();
		}

		return nullptr;
	}

	std::unique_ptr<EnemyState> EnemyWalkingState::GetHit(EnemyComponent* snobee, GameObject* block)
	{
		snobee->GetOwner()->SetParent(block, false);
		return std::make_unique<EnemySlidingState>();
	}

	// Breaking State
	//============================================================================================================================================================================================
	void EnemyBreakingState::Enter(EnemyComponent* snobee)
	{
		m_TexturePtr = snobee->GetTexture();
		m_Direction = snobee->GetDirection();
		if (m_Direction.x < 0)
		{
			m_TexturePtr->SetSourceRect(32, 160);
		}
		if (m_Direction.x > 0)
		{
			m_TexturePtr->SetSourceRect(96, 160);
		}
		if (m_Direction.y < 0)
		{
			m_TexturePtr->SetSourceRect(64, 160);
		}
		if (m_Direction.y > 0)
		{
			m_TexturePtr->SetSourceRect(0, 160);
		}

		m_Direction = snobee->GetDirection();
		auto goTransform = snobee->GetOwner()->GetTransform();
		auto currentPos = goTransform->GetWorldPosition();
		m_TargetPosition = snobee->GetOwner()->GetWorldPosition();
		m_TargetPosition = snobee->GetGrid()->RequestMove(currentPos, m_Direction);
	}

	std::unique_ptr<EnemyState> EnemyBreakingState::Update(EnemyComponent* snobee, float deltaTime)
	{
		auto transform = snobee->GetOwner()->GetTransform();
		glm::vec3 direction = (m_TargetPosition - transform->GetWorldPosition());

		float sqrLength = glm::dot(direction, direction);
		if (sqrLength < 4)
		{
			transform->SetLocalPosition(m_TargetPosition - transform->GetWorldPosition() + transform->GetLocalPosition());
			return std::make_unique<EnemyWalkingState>();
		}
		else
		{
			float length = std::sqrt(sqrLength);
			direction.x /= length;
			direction.y /= length;

			direction.x *= (snobee->GetSpeed() * deltaTime / 2.f);
			direction.y *= (snobee->GetSpeed() * deltaTime / 2.f);

			if (m_TargetPosition.x != FLT_MAX)
				transform->Move(direction);
		}
		Animate(snobee, deltaTime);

		return nullptr;
	}

	void EnemyBreakingState::Animate(EnemyComponent* snobee, float deltaTime)
	{
		m_TotalDT += deltaTime;
		if (m_TotalDT > FRAME_DELAY)
		{
			m_TotalDT -= FRAME_DELAY;

			if (snobee->GetOwner()->GetWorldPosition() != m_TargetPosition && m_TargetPosition.x != FLT_MAX)
				++m_CurrentFrame %= 2;
			else
				m_CurrentFrame = 0;

			int currentFrameOffset = 16 * m_CurrentFrame;

			if (m_Direction.x < 0)
			{
				m_TexturePtr->SetSourceRect(32 + currentFrameOffset, 160);
			}
			if (m_Direction.x > 0)
			{
				m_TexturePtr->SetSourceRect(96 + currentFrameOffset, 160);
			}
			if (m_Direction.y < 0)
			{
				m_TexturePtr->SetSourceRect(64 + currentFrameOffset, 160);
			}
			if (m_Direction.y > 0)
			{
				m_TexturePtr->SetSourceRect(currentFrameOffset, 160);
			}
		}
	}

	void EnemyBreakingState::Exit(EnemyComponent* snobee)
	{
		snobee->GetOwner()->SetLocalPosition(snobee->GetGrid()->PointToGridPos(snobee->GetOwner()->GetWorldPosition()) - snobee->GetOwner()->GetWorldPosition() + snobee->GetOwner()->GetLocalPosition());
	}

	std::unique_ptr<EnemyState> EnemyBreakingState::OnMove(EnemyComponent* )
	{
		return nullptr;
	}

	std::unique_ptr<EnemyState> EnemyBreakingState::Break(EnemyComponent* )
	{
		return nullptr;
	}

	std::unique_ptr<EnemyState> EnemyBreakingState::GetHit(EnemyComponent* snobee, GameObject* block)
	{
		snobee->GetOwner()->SetParent(block, false);
		return std::make_unique<EnemySlidingState>();
	}

	// Spawning State
	//============================================================================================================================================================================================
	void EnemySpawningState::Enter(EnemyComponent* snobee)
	{
		m_TexturePtr = snobee->GetTexture();
		m_TexturePtr->SetSourceRect(0,128);
		m_TargetPosition = snobee->GetOwner()->GetWorldPosition();
	}

	std::unique_ptr<EnemyState> EnemySpawningState::Update(EnemyComponent* snobee, float deltaTime)
	{
		if (m_CurrentFrame > 7)
		{
			return std::make_unique<EnemyWalkingState>();
		}
		Animate(snobee, deltaTime);
		return nullptr;
	}

	void EnemySpawningState::Animate(EnemyComponent* , float deltaTime)
	{
		m_TotalDT += deltaTime;
		if (m_TotalDT > FRAME_DELAY)
		{
			m_TotalDT -= FRAME_DELAY;
			++m_CurrentFrame;

			m_TexturePtr->SetSourceRect(16 * m_CurrentFrame, 128);
		}
	}

	void EnemySpawningState::Exit(EnemyComponent* )
	{
	}

	std::unique_ptr<EnemyState> EnemySpawningState::OnMove(EnemyComponent* )
	{
		return nullptr;
	}
	std::unique_ptr<EnemyState> EnemySpawningState::Break(EnemyComponent* )
	{
		return nullptr;
	}

	std::unique_ptr<EnemyState> EnemySpawningState::GetHit(EnemyComponent* snobee, GameObject* block)
	{
		snobee->GetOwner()->SetParent(block, false);
		return std::make_unique<EnemySlidingState>();
	}

	// Stunned State
	//============================================================================================================================================================================================
	void EnemyStunnedState::Enter(EnemyComponent* )
	{

	}

	std::unique_ptr<EnemyState> EnemyStunnedState::Update(EnemyComponent* , float )
	{
		return std::unique_ptr<EnemyState>();
	}

	void EnemyStunnedState::Animate(EnemyComponent* , float )
	{

	}

	void EnemyStunnedState::Exit(EnemyComponent* )
	{

	}

	std::unique_ptr<EnemyState> EnemyStunnedState::OnMove(EnemyComponent* )
	{
		return nullptr;
	}

	std::unique_ptr<EnemyState> EnemyStunnedState::Break(EnemyComponent* )
	{
		return nullptr;
	}

	std::unique_ptr<EnemyState> EnemyStunnedState::GetHit(EnemyComponent* snobee, GameObject* block)
	{
		snobee->GetOwner()->SetParent(block, false);
		return std::make_unique<EnemySlidingState>();
	}

	// Sliding State
	//============================================================================================================================================================================================
	void EnemySlidingState::Enter(EnemyComponent* snobee)
	{
		m_TilePtr = snobee->GetOwner()->GetParent()->GetComponent<TileComponent>();
	}

	std::unique_ptr<EnemyState> EnemySlidingState::Update(EnemyComponent* snobee, float)
	{
		if (!m_TilePtr->IsSliding())
		{
			snobee->GetOwner()->NotifyObservers(Event{make_sdbm_hash("EnemyDied"), nullptr});
			snobee->GetOwner()->Destroy();
		}

		return nullptr;
	}

	void EnemySlidingState::Animate(EnemyComponent* , float)
	{

	}

	void EnemySlidingState::Exit(EnemyComponent* )
	{
		
	}

	std::unique_ptr<EnemyState> EnemySlidingState::OnMove(EnemyComponent* )
	{
		return nullptr;
	}

	std::unique_ptr<EnemyState> EnemySlidingState::Break(EnemyComponent* )
	{
		return nullptr;
	}
	std::unique_ptr<EnemyState> EnemySlidingState::GetHit(EnemyComponent* , GameObject* )
	{
		return nullptr;
	}
}