#include "TileComponent.h"
#include "GameObject.h"
#include <iostream>
#include "EventArgs.h"

namespace dae
{
	TileComponent::TileComponent(GameObject* owner, Tile tileType, float x, float y, GridComponent* grid):
		CppBehaviour{ owner }, m_Pos {
		x, y, 0
	}, FRAME_DELAY{ 0.1f }, m_BlockState{ BlockState::Still }, m_TileType{ tileType }, m_GridPtr{ grid }, m_SlideSpeed{ 700.f }
	{
	}

	void TileComponent::Start()
	{
		m_Texture = m_OwningGameObject->GetComponent<dae::TextureComponent>();
	}

	void TileComponent::Slide(const glm::vec3& direction)
	{
		m_BlockState = BlockState::Sliding;
		m_SlideDirection = direction;
	}

	bool TileComponent::Destroy(bool pushedByPengo)
	{
		if (m_TileType != Tile::Unbreakable)
		{
			m_BlockState = BlockState::Breaking;
			if(m_Texture)
				m_Texture->SetSourceRect(0, 48);
			m_TotalDT = 0.f;
			m_CurrentFrame = 0;
			if(pushedByPengo)
				m_OwningGameObject->NotifyObservers(Event{ make_sdbm_hash("EnemyDied"), nullptr });

			return true;
		}
		return false;
	}

	bool TileComponent::IsSliding()
	{
		return m_BlockState == BlockState::Sliding;
	}

	bool TileComponent::IsBreaking()
	{
		return m_BlockState == BlockState::Breaking;
	}

	void TileComponent::Update(float deltaTime)
	{
		switch (m_BlockState)
		{
		case BlockState::Still:
		{
			if (m_TileType == Tile::Sno_Bee)
			{
				m_TotalDT += deltaTime;
				if (m_TotalDT > FRAME_DELAY)
				{
					m_TotalDT -= FRAME_DELAY;
					++m_CurrentFrame;

					if (m_CurrentFrame < 9)
					{
						int frameNr = m_CurrentFrame % 2;
						m_Texture->SetSourceRect(16 * frameNr, 0);
					}
				}
			}
		}
		break;
		case BlockState::Breaking:
		{
			m_TotalDT += deltaTime;
			if (m_TotalDT > FRAME_DELAY)
			{
				m_TotalDT -= FRAME_DELAY;
				++m_CurrentFrame;

				m_Texture->SetSourceRect(16 * m_CurrentFrame, 48);
				if (m_CurrentFrame > 6)
				{
					m_OwningGameObject->Destroy();
				}
			}
		}
		break;
		case BlockState::Sliding:
		{
			TileMoveArg args = TileMoveArg{ this, m_Pos, m_SlideDirection };
			m_OwningGameObject->NotifyObservers(Event{ make_sdbm_hash("TileMoved"), &args });

			m_Pos = m_OwningGameObject->GetWorldPosition();
			if (m_Pos == m_TargetPosition || m_TargetPosition.x == FLT_MAX)
			{
				m_TargetPosition = m_GridPtr->RequestMove(m_Pos, m_SlideDirection, true);

				if (m_TargetPosition == m_Pos)
					m_BlockState = BlockState::Still;
			}
			else
			{
				glm::vec3 direction = (m_TargetPosition - m_Pos);
				
				float sqrLength = direction.x * direction.x + direction.y * direction.y;
				if (sqrLength < 64)
				{
					m_OwningGameObject->GetTransform()->SetLocalPosition(m_TargetPosition - m_Pos + m_OwningGameObject->GetLocalPosition());
				}
				else
				{
					float length = std::sqrt(sqrLength);
					direction.x /= length;
					direction.y /= length;

					direction.x *= (m_SlideSpeed * deltaTime);
					direction.y *= (m_SlideSpeed * deltaTime);

					m_OwningGameObject->GetTransform()->Move(direction);
				}
			}
		}
		break;
		}
		
	}
}