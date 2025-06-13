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
			m_TexturePtr->SetSourceRect(LVL_TEXTURE_OFSETT.x + 32, LVL_TEXTURE_OFSETT.y + 32);
		}
		if (m_Direction.x > 0)
		{
			m_TexturePtr->SetSourceRect(LVL_TEXTURE_OFSETT.x + 96, LVL_TEXTURE_OFSETT.y + 32);
		}
		if (m_Direction.y < 0)
		{
			m_TexturePtr->SetSourceRect(LVL_TEXTURE_OFSETT.x + 64, LVL_TEXTURE_OFSETT.y + 32);
		}
		if (m_Direction.y > 0)
		{
			m_TexturePtr->SetSourceRect(LVL_TEXTURE_OFSETT.x, LVL_TEXTURE_OFSETT.y + 32);
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
				m_TexturePtr->SetSourceRect(LVL_TEXTURE_OFSETT.x + 32 + currentFrameOffset, LVL_TEXTURE_OFSETT.y + 32);
			}
			if (m_Direction.x > 0)
			{
				m_TexturePtr->SetSourceRect(LVL_TEXTURE_OFSETT.x + 96 + currentFrameOffset, LVL_TEXTURE_OFSETT.y + 32);
			}
			if (m_Direction.y < 0)
			{
				m_TexturePtr->SetSourceRect(LVL_TEXTURE_OFSETT.x + 64 + currentFrameOffset, LVL_TEXTURE_OFSETT.y + 32);
			}
			if (m_Direction.y > 0)
			{
				m_TexturePtr->SetSourceRect(LVL_TEXTURE_OFSETT.x + currentFrameOffset, LVL_TEXTURE_OFSETT.y + 32);
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

	std::unique_ptr<EnemyState> EnemyWalkingState::Reset(EnemyComponent* snobee, int idx)
	{
		snobee->GetOwner()->SetLocalPosition(snobee->GetGrid()->IdxToPoint(idx));
		m_TargetPosition = snobee->GetOwner()->GetWorldPosition();
		return nullptr;
	}

	std::unique_ptr<EnemyState> EnemyWalkingState::GetStunned(EnemyComponent*)
	{
		return std::make_unique<EnemyStunnedState>();
	}

	// Breaking State
	//============================================================================================================================================================================================
	void EnemyBreakingState::Enter(EnemyComponent* snobee)
	{
		m_TexturePtr = snobee->GetTexture();
		m_Direction = snobee->GetDirection();
		if (m_Direction.x < 0)
		{
			m_TexturePtr->SetSourceRect(LVL_TEXTURE_OFSETT.x + 32, LVL_TEXTURE_OFSETT.y + 32);
		}
		if (m_Direction.x > 0)
		{
			m_TexturePtr->SetSourceRect(LVL_TEXTURE_OFSETT.x + 96, LVL_TEXTURE_OFSETT.y + 32);
		}
		if (m_Direction.y < 0)
		{
			m_TexturePtr->SetSourceRect(LVL_TEXTURE_OFSETT.x + 64, LVL_TEXTURE_OFSETT.y + 32);
		}
		if (m_Direction.y > 0)
		{
			m_TexturePtr->SetSourceRect(LVL_TEXTURE_OFSETT.x, LVL_TEXTURE_OFSETT.y + 32);
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
				m_TexturePtr->SetSourceRect(LVL_TEXTURE_OFSETT.x + 32 + currentFrameOffset, LVL_TEXTURE_OFSETT.y + 32);
			}
			if (m_Direction.x > 0)
			{
				m_TexturePtr->SetSourceRect(LVL_TEXTURE_OFSETT.x + 96 + currentFrameOffset, LVL_TEXTURE_OFSETT.y + 32);
			}
			if (m_Direction.y < 0)
			{
				m_TexturePtr->SetSourceRect(LVL_TEXTURE_OFSETT.x + 64 + currentFrameOffset, LVL_TEXTURE_OFSETT.y + 32);
			}
			if (m_Direction.y > 0)
			{
				m_TexturePtr->SetSourceRect(LVL_TEXTURE_OFSETT.x + currentFrameOffset, LVL_TEXTURE_OFSETT.y + 32);
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

	std::unique_ptr<EnemyState> EnemyBreakingState::Reset(EnemyComponent* snobee, int idx)
	{
		snobee->GetOwner()->SetLocalPosition(snobee->GetGrid()->IdxToPoint(idx));
		return std::make_unique<EnemyWalkingState>();
	}

	std::unique_ptr<EnemyState> EnemyBreakingState::GetStunned(EnemyComponent* )
	{
		return std::make_unique<EnemyStunnedState>();
	}

	// Spawning State
	//============================================================================================================================================================================================
	void EnemySpawningState::Enter(EnemyComponent* snobee)
	{
		m_TexturePtr = snobee->GetTexture();
		m_TexturePtr->SetSourceRect(LVL_TEXTURE_OFSETT.x, LVL_TEXTURE_OFSETT.y);
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

			m_TexturePtr->SetSourceRect(LVL_TEXTURE_OFSETT.x + 16 * m_CurrentFrame, LVL_TEXTURE_OFSETT.y);
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

	std::unique_ptr<EnemyState> EnemySpawningState::Reset(EnemyComponent* snobee, int idx)
	{
		snobee->GetOwner()->SetLocalPosition(snobee->GetGrid()->IdxToPoint(idx));
		return std::make_unique<EnemyWalkingState>();
	}

	std::unique_ptr<EnemyState> EnemySpawningState::GetStunned(EnemyComponent* )
	{
		return std::make_unique<EnemyStunnedState>();
	}

	// Stunned State
	//============================================================================================================================================================================================
	void EnemyStunnedState::Enter(EnemyComponent* snobee)
	{
		m_TexturePtr = snobee->GetTexture();
		m_Direction = snobee->GetDirection();
		m_TexturePtr->SetSourceRect(LVL_TEXTURE_OFSETT.x + 96, LVL_TEXTURE_OFSETT.y);
		snobee->isStunned = true;
	}

	std::unique_ptr<EnemyState> EnemyStunnedState::Update(EnemyComponent* snobee, float deltaTime)
	{
		m_StunDuration += deltaTime;
		if (m_StunDuration > STUN_DURATION)
			return std::make_unique<EnemyWalkingState>();

		Animate(snobee, deltaTime);
		return nullptr;
	}

	void EnemyStunnedState::Animate(EnemyComponent* , float deltaTime)
	{
		m_TotalDT += deltaTime;
		if (m_TotalDT > FRAME_DELAY)
		{
			m_TotalDT -= FRAME_DELAY;
			m_CurrentFrame = ++m_CurrentFrame % 2;
			m_TexturePtr->SetSourceRect(LVL_TEXTURE_OFSETT.x + 96 + 16 * m_CurrentFrame, LVL_TEXTURE_OFSETT.y);
		}
	}

	void EnemyStunnedState::Exit(EnemyComponent* snobee)
	{
		snobee->isStunned = false;
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

	std::unique_ptr<EnemyState> EnemyStunnedState::Reset(EnemyComponent* snobee, int idx)
	{
		snobee->GetOwner()->SetLocalPosition(snobee->GetGrid()->IdxToPoint(idx));
		return std::make_unique<EnemyWalkingState>();
	}

	std::unique_ptr<EnemyState> EnemyStunnedState::GetStunned(EnemyComponent*)
	{
		return nullptr;
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
			if(!m_IsDead)
			{
				snobee->GetOwner()->NotifyObservers(Event{ make_sdbm_hash("EnemyDied"), nullptr });
				snobee->GetOwner()->Destroy();
				m_IsDead = true;
			}
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
	std::unique_ptr<EnemyState> EnemySlidingState::Reset(EnemyComponent* snobee, int idx)
	{
		snobee->GetOwner()->SetLocalPosition(snobee->GetGrid()->IdxToPoint(idx));
		return std::make_unique<EnemyWalkingState>();
	}
	std::unique_ptr<EnemyState> EnemySlidingState::GetStunned(EnemyComponent* )
	{
		return nullptr;
	}
}