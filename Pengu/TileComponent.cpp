#include "TileComponent.h"
#include "GameObject.h"
#include <iostream>

namespace dae
{
	TileComponent::TileComponent(const Tile& tileType, float x, float y, float tileSize):m_Pos{x,y}, TILE_SIZE{tileSize}, FRAME_DELAY{0.1f}
	{
		m_TileType = tileType;

	}


	void TileComponent::Slide(const glm::vec2& )
	{
		std::cout << "i be slidin\n";
	}

	bool TileComponent::Destroy()
	{
		if (m_TileType == Tile::Breakable)
		{
			m_Break = true;
			m_Texture->SetSourceRect(0, 48);
			return true;
		}
		return false;
	}

	void TileComponent::Update(float deltaTime)
	{
		if (m_Break)
		{
			totalDT += deltaTime;
			if (totalDT > FRAME_DELAY)
			{
				totalDT -= FRAME_DELAY;
				++m_CurrentFrame;

				m_Texture->SetSourceRect(16 * m_CurrentFrame, 48);
				if (m_CurrentFrame > 8)
				{
					m_OwningGameObject->SetParent(nullptr, true);
					m_OwningGameObject->pendingRemove = true;
				}
			}
		}
		if (!tileSet)
		{
			switch (m_TileType)
			{
			case Tile::Breakable:
			{
				m_Texture = m_OwningGameObject->AddComponent<TextureComponent>();
				m_Texture->SetTexture("Blocks.png");
				m_Texture->SetSourceRect(0, 0, 16, 16);
				m_Texture->SetWidthAndHeight(TILE_SIZE,TILE_SIZE);
				
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
}