#include "GridComponent.h"
#include <fstream>
#include <iostream>
#include "GameObject.h"
#include "SceneManager.h"
#include "TileComponent.h"
#include "Scene.h"

namespace dae
{
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


		for (int idx{}; idx < m_GridPtr->size(); ++idx)
		{

			auto go = std::make_shared<dae::GameObject>();
			go->AddComponent<TileComponent>(m_GridPtr->at(idx), GRID_OFSETT.x + static_cast<float>( TILE_WIDTH * (idx % WIDTH)), GRID_OFSETT.y + static_cast<float>(TILE_WIDTH * (idx / WIDTH)),static_cast<float>(TILE_WIDTH));
			scene.Add(go);
		}

		file.close();

	}

	glm::vec3 GridComponent::RequestMove(const glm::vec3& currentPos,glm::vec2& direction)
	{
		glm::vec2 indexPos = { ((currentPos.x - GRID_OFSETT.x) + (TILE_WIDTH / 2)) / TILE_WIDTH ,
							   ((currentPos.y - GRID_OFSETT.y) + (TILE_WIDTH / 2)) / TILE_WIDTH };

		int idx = static_cast<int>(indexPos.x) + static_cast<int>(indexPos.y) * WIDTH;
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

		if (idx < 0 || idx > m_GridPtr->size() - 1)
		{
			return currentPos;
		}

		if (m_GridPtr->at(idx) == Tile::Empty)
		{
			return { GRID_OFSETT.x + static_cast<float>(TILE_WIDTH * (idx % WIDTH)), 
					 GRID_OFSETT.y + static_cast<float>(TILE_WIDTH * (idx / WIDTH)),
					 0 };
		}

		return currentPos;
	}

	GridComponent::GridComponent(int width, int height, int tileWidth, glm::vec2 gridOfsett):
		WIDTH{width}, HEIGHT{height}, TILE_WIDTH{tileWidth}, GRID_OFSETT{gridOfsett}
	{
		m_GridPtr = std::make_unique<std::vector<Tile>>();
		m_GridPtr->clear();
	}
}