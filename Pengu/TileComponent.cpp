#include "TileComponent.h"
#include "GameObject.h"
#include <iostream>

namespace dae
{
	TileComponent::TileComponent(const Tile& tileType, float x, float y, float tileSize):m_Pos{x,y}, TILE_SIZE{tileSize}
	{
		m_TileType = tileType;

	}


	void TileComponent::Update(float)
	{
		if (!tileSet)
		{
			switch (m_TileType)
			{
			case Tile::Breakable:
			{
				m_Texture = m_OwningGameObject->AddComponent<TextureComponent>();
				m_Texture->SetTexture("BreakableBlock.png");
				m_Texture->SetWidthAndHeight(TILE_SIZE,TILE_SIZE);
				
			}
			break;
			case Tile::Unbreakable:
			{
				m_Texture = m_OwningGameObject->AddComponent<TextureComponent>();
				m_Texture->SetTexture("UnbreakableBlock.png");
				m_Texture->SetWidthAndHeight(TILE_SIZE, TILE_SIZE);
			}
			break;
			}

			m_OwningGameObject->SetLocalPosition(m_Pos.x, m_Pos.y);

			tileSet = true;
		}
		
	}
}