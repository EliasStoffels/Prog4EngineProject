#include "WallComponent.h"
#include "GameObject.h"

namespace dae
{
	void WallComponent::Update(float deltaTime)
	{
		if (!m_Shake)
			return;

		m_TotalDT += deltaTime;

		if (m_TotalDT >= m_FrameDelay)
		{
			m_TotalDT -= m_FrameDelay;
			++m_Currentframe;

			m_VertWallTex->SetSourceRect(12 * (m_Currentframe % 2), 0, 8, 256);
			m_HorWallTex->SetSourceRect(0, 12 * (m_Currentframe % 2), 256, 8);

			if (m_Currentframe > FRAMES)
			{
				m_VertWallTex->IsActive(false);
				m_HorWallTex->IsActive(false);
			
				m_TotalDT = 0;
				m_Currentframe = 0;
				m_Shake = false;
			}
		}


	}
	void WallComponent::ShakeWall(DirectionState direction)
	{
		if (m_Shake)
			return;

		m_Shake = true;
		switch (direction)
		{
		case DirectionState::Left:
		{
			m_OwningGameObject->SetLocalPosition(GRID_OFSETT.x - WALL_WIDTH,GRID_OFSETT.y - WALL_WIDTH);
			m_VertWallTex->IsActive(true);
		}
		break;
		case DirectionState::Right:
		{
			m_OwningGameObject->SetLocalPosition(GRID_OFSETT.x + GRID_SIZE.x, GRID_OFSETT.y - WALL_WIDTH);
			m_VertWallTex->IsActive(true);
		}
		break;
		case DirectionState::Up:
		{
			m_OwningGameObject->SetLocalPosition(GRID_OFSETT.x - WALL_WIDTH, GRID_OFSETT.y - WALL_WIDTH);
			m_HorWallTex->IsActive(true);
		}
		break;
		case DirectionState::Down:
		{
			m_OwningGameObject->SetLocalPosition(GRID_OFSETT.x - WALL_WIDTH, GRID_OFSETT.y + GRID_SIZE.y);
			m_HorWallTex->IsActive(true);
		}
		break;
		}
	}
	WallComponent::WallComponent(const glm::vec2& gridOfsett, const glm::vec2& gridSize, TextureComponent* vertWallTex, TextureComponent* horWallTex):
		GRID_OFSETT{gridOfsett},GRID_SIZE{gridSize}, m_VertWallTex{vertWallTex}, m_HorWallTex{horWallTex}
	{
		m_VertWallTex->SetWidthAndHeight(WALL_WIDTH, GRID_SIZE.y + WALL_WIDTH*2);
		m_VertWallTex->SetSourceRect(0,0,8,256);
		m_HorWallTex->SetWidthAndHeight(GRID_SIZE.x + WALL_WIDTH*2 , WALL_WIDTH);
		m_HorWallTex->SetSourceRect(0, 0, 256, 8);
	}
}
