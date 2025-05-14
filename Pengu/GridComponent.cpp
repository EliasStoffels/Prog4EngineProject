#include "GridComponent.h"
#include <fstream>
#include <iostream>
#include "GameObject.h"
#include "SceneManager.h"
#include "TileComponent.h"
#include "TextureComponent.h"
#include "Scene.h"
#include "WallComponent.h"

namespace dae
{
	auto FindInVector(std::vector<std::pair<int, TileComponent*>>& vec, int idx) {
		return std::find_if(vec.begin(), vec.end(),
			[idx](const auto& pair) { return pair.first == idx; });
	}

	void GridComponent::SaveLevel()
	{
		//row 1
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Empty);

		//row 2
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Empty);

		//row 3
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Empty);

		//row 4
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Empty);

		//row 5
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);

		//row 6
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Unbreakable);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Empty);

		//row 7
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Empty);

		//row 8
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Breakable);

		//row 9
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
				 
		//row 10 
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Empty);
				
		//row 11
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
				 
		//row 12 
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Unbreakable);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Breakable);
				 
		//row 13 
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
				 
		//row 14 
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Unbreakable);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Empty);
				 
		//row 15 
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Breakable);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);
		m_GridPtr->emplace_back(Tile::Empty);


		std::ofstream file{};
		file.open("../data/levels.bin", std::ios::binary);
		if (!file.is_open())
		{
			std::cerr << "error opening file\n";
		}

		file.write(reinterpret_cast<const char*>(m_GridPtr->data()), m_GridPtr->size() * sizeof(Tile));
		file.close();
	}

	void GridComponent::LoadLevel(int )
	{
		const size_t numTiles = WIDTH * HEIGHT;
		m_GridPtr->resize(numTiles);

		std::ifstream file("../data/levels.bin", std::ios::binary);
		if (!file.is_open())
		{
			std::cerr << "Error opening file\n";
			return;
		}

		file.read(reinterpret_cast<char*>(m_GridPtr->data()), numTiles * sizeof(Tile));
		
		auto& scene = dae::SceneManager::GetInstance().GetScene("Pengo");


		for (unsigned int idx{}; idx < m_GridPtr->size(); ++idx)
		{
			auto tileType = m_GridPtr->at(idx);
			if (tileType != Tile::Empty)
			{
				auto go = std::make_shared<dae::GameObject>();
				auto tilePos = IdxToPoint(idx);
				auto tileC = go->AddComponent<TileComponent>(tileType, tilePos.x, tilePos.y, static_cast<float>(TILE_WIDTH), this);
				m_Blocks.emplace_back(std::pair<int, TileComponent*>(idx, tileC));
				scene.Add(go);
			}
		}

		file.close();

	}

	glm::vec3 GridComponent::RequestMove(const glm::vec3& currentPos,glm::vec3& direction, bool isBlock)
	{
		int origIdx = PointToIdx(glm::vec3{ currentPos.x + (TILE_WIDTH / 2),currentPos.y + (TILE_WIDTH / 2),0 });
		int idx = origIdx;
		if (direction.x < 0 && idx% WIDTH != 0)
		{
			--idx;
		}
		if (direction.x > 0 && idx % WIDTH != (WIDTH - 1))
		{
			++idx;
		}
		if (direction.y < 0 && idx/WIDTH != 0)
		{
			idx -= WIDTH;
		}
		if (direction.y > 0 && idx/ WIDTH != (HEIGHT - 1))
		{
			idx += WIDTH;
		}

		if (m_GridPtr->at(idx) == Tile::Empty)
		{
			if (isBlock)
			{
				m_GridPtr->at(idx) = m_GridPtr->at(origIdx);
				m_GridPtr->at(origIdx) = Tile::Empty;
				auto it = FindInVector(m_Blocks, origIdx);
				if (it != m_Blocks.end())
				{
					it->first = idx;
				}
			}
			return IdxToPoint(idx);
		}
		return currentPos;
	}

	BlockState GridComponent::RequestPush(const glm::vec3& currentPos, const glm::vec3& direction)
	{
		int idx = PointToIdx(glm::vec3{ currentPos.x + (TILE_WIDTH / 2),currentPos.y + (TILE_WIDTH / 2),0 });
		int idxBehind = 0;
		if (direction.x < 0)
		{
			if (idx % WIDTH != 0)
			{
				--idx;
				idxBehind = idx - 1;
			}
			else
			{
				m_Walls->ShakeWall(DirectionState::Left);
				return BlockState::Breaking;
			}
		}
		if (direction.x > 0 )
		{
			if(idx % WIDTH != (WIDTH - 1))
			{
				++idx;
				idxBehind = idx + 1;
			}
			else
			{
				m_Walls->ShakeWall(DirectionState::Right);
				return BlockState::Breaking;
			}
		}
		if (direction.y < 0)
		{
			if (idx / WIDTH != 0)
			{
				idx -= WIDTH;
				idxBehind = idx - WIDTH;
			}
			else
			{
				m_Walls->ShakeWall(DirectionState::Up);
				return BlockState::Breaking;
			}
		}
		if (direction.y > 0)
		{
			if (idx / WIDTH != (HEIGHT - 1))
			{
				idx += WIDTH;
				idxBehind = idx + WIDTH;
			}
			else
			{
				m_Walls->ShakeWall(DirectionState::Down);
				return BlockState::Breaking;
			}
		}

		/*if (idx < 0 || idx > static_cast<int>(m_GridPtr->size() - 1))
		{
			return BlockState::Breaking;
		}*/

		if (m_GridPtr->at(idx) != Tile::Empty)
		{
			if (idxBehind < 0 || idxBehind > static_cast<int>(m_GridPtr->size() - 1) ||		// out of range (push top and bottom blocks against edge)
				m_GridPtr->at(idxBehind) != Tile::Empty ||									// another block behind
				idx % WIDTH == 0 && direction.x < 0 ||										// pushing left against a block against the left wall
				idx % WIDTH == (WIDTH - 1) && direction.x > 0)								// pushing right against a block against the right wall
			{
				auto it = FindInVector(m_Blocks, idx);
				if (it != m_Blocks.end() && it->second->Destroy()) 
				{
					m_GridPtr->at(idx) = Tile::Empty;
					m_Blocks.erase(it);
				}
				return BlockState::Breaking;
			}
			else
			{
				auto it = FindInVector(m_Blocks, idx);
				if (it != m_Blocks.end()) 
				{
					it->second->Slide(direction);
				}
				return BlockState::Sliding;
			}
			
		}

		return BlockState::Still;
	}

	int GridComponent::PointToIdx(const glm::vec3 position)
	{
		glm::vec2 indexPos = { ((position.x - GRID_OFSETT.x)) / TILE_WIDTH ,
							   ((position.y - GRID_OFSETT.y)) / TILE_WIDTH };

		int idx = static_cast<int>(indexPos.x) + static_cast<int>(indexPos.y) * WIDTH;

		return idx;
	}

	glm::vec3 GridComponent::IdxToPoint(int idx)
	{
		return { GRID_OFSETT.x + static_cast<float>(TILE_WIDTH * (idx % WIDTH)),
				 GRID_OFSETT.y + static_cast<float>(TILE_WIDTH * (idx / WIDTH)),
				 0 };
	}

	GridComponent::GridComponent(int width, int height, int tileWidth, glm::vec2 gridOfset, WallComponent* walls):
		WIDTH{width}, HEIGHT{height}, TILE_WIDTH{tileWidth}, GRID_OFSETT{ gridOfset }, m_Walls{ walls }
	{
		m_GridPtr = std::make_unique<std::vector<Tile>>();
	}
}