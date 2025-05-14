#include "TileComponent.h"
#include "GameObject.h"
#include <iostream>

namespace dae
{
	TileComponent::TileComponent(Tile tileType, float x, float y, float tileSize, GridComponent* grid):
		m_Pos{x,y,0}, TILE_SIZE{tileSize}, FRAME_DELAY{0.1f}, m_BlockState{BlockState::Still}, m_TileType{tileType}, m_GridPtr{grid}, m_SlideSpeed{700.f}
	{
		m_TileType = tileType;
	}


	void TileComponent::Slide(const glm::vec3& direction)
	{
		m_BlockState = BlockState::Sliding;
		m_SlideDirection = direction;
	}

	bool TileComponent::Destroy()
	{
		if (m_TileType == Tile::Breakable)
		{
			m_BlockState = BlockState::Breaking;
			m_Texture->SetSourceRect(0, 48);
			return true;
		}
		return false;
	}

	void TileComponent::Update(float deltaTime)
	{
		switch (m_BlockState)
		{
		case BlockState::Still:
		{
			if (!tileSet)
			{
				switch (m_TileType)
				{
				case Tile::Breakable:
				{
					m_Texture = m_OwningGameObject->AddComponent<TextureComponent>();
					m_Texture->SetTexture("Blocks.png");
					m_Texture->SetSourceRect(0, 0, 16, 16);
					m_Texture->SetWidthAndHeight(TILE_SIZE, TILE_SIZE);

				}
				break;
				case Tile::Unbreakable:
				{
					m_Texture = m_OwningGameObject->AddComponent<TextureComponent>();
					m_Texture->SetTexture("Blocks.png");
					m_Texture->SetSourceRect(0, 16, 16, 16);
					m_Texture->SetWidthAndHeight(TILE_SIZE, TILE_SIZE);
				}
				break;
				}

				m_OwningGameObject->SetLocalPosition(m_Pos.x, m_Pos.y);

				tileSet = true;
			}
		}
		break;
		case BlockState::Breaking:
		{
			totalDT += deltaTime;
			if (totalDT > FRAME_DELAY)
			{
				totalDT -= FRAME_DELAY;
				++m_CurrentFrame;

				m_Texture->SetSourceRect(16 * m_CurrentFrame, 48);
				if (m_CurrentFrame > 8)
				{
					m_OwningGameObject->Destroy();
				}
			}
		}
		break;
		case BlockState::Sliding:
		{
			m_Pos = m_OwningGameObject->GetWorldPosition();
			if (m_Pos == m_TargetPosition || m_TargetPosition.x == FLT_MAX)
			{
				glm::vec3 requestResult = m_TargetPosition = m_GridPtr->RequestMove(m_Pos, m_SlideDirection, true);

				if (requestResult == m_Pos)
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