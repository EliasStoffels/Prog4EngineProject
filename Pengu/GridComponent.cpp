#include "GridComponent.h"
#include <fstream>
#include <iostream>
#include "GameObject.h"
#include "SceneManager.h"
#include "TileComponent.h"
#include "TextureComponent.h"
#include "Scene.h"
#include "WallComponent.h"
#include <random>
#include "EnemyControllerComponent.h"
#include "GameStateManager.h"
#include "EventArgs.h"

namespace dae
{
	auto FindInVector(std::vector<std::pair<int, TileComponent*>>& vec, int idx) {
		return std::find_if(vec.begin(), vec.end(),
			[idx](const auto& pair) { return pair.first == idx; });
	}

	void GridComponent::LoadLevel(EnemyControllerComponent* enemyController, int level)
	{
		const size_t numTiles = WIDTH * HEIGHT;
		m_GridPtr->resize(numTiles);

		std::ifstream file("../data/levels.bin", std::ios::binary);
		if (!file.is_open())
		{
			std::cerr << "Error opening file\n";
			return;
		}

		file.seekg(level * numTiles * sizeof(Tile), std::ios::beg);

		file.read(reinterpret_cast<char*>(m_GridPtr->data()), numTiles * sizeof(Tile));
		file.close();
		
		RandomiseSnobee();

		auto& scene = dae::SceneManager::GetInstance().GetScene();

		for (unsigned int idx{}; idx < m_GridPtr->size(); ++idx)
		{
			auto tileType = m_GridPtr->at(idx);
			if (tileType != Tile::Empty)
			{
				auto go = scene.AddEmpty();
				auto tilePos = IdxToPoint(idx);
				auto tileC = go->AddComponent<TileComponent>(tileType, tilePos.x, tilePos.y, this);
				switch (tileType)
				{
				case Tile::Sno_Bee:
				case Tile::Breakable:
				{
					auto texture = go->AddComponent<TextureComponent>();
					texture->SetTexture("Blocks.png");
					texture->SetSourceRect(0, 0, 16, 16);
					texture->SetWidthAndHeight(static_cast<float>(TILE_WIDTH), static_cast<float>(TILE_WIDTH));
				}
				break;
				case Tile::Unbreakable:
				{
					auto texture = go->AddComponent<TextureComponent>();
					texture->SetTexture("Blocks.png");
					texture->SetSourceRect(0, 16, 16, 16);
					texture->SetWidthAndHeight(static_cast<float>(TILE_WIDTH), static_cast<float>(TILE_WIDTH));
				}
				break;
				}
				go->SetLocalPosition(tilePos.x, tilePos.y);
				go->AddObserver(enemyController);

				m_Blocks.emplace_back(std::pair<int, TileComponent*>(idx, tileC));
			}
		}

		GameStateManager::GetInstance().StartLevel();
	}

	glm::vec3 GridComponent::RequestMove(const glm::vec3& currentPos,const glm::vec3& direction, bool isBlock)
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

		auto blockBreakingCheck = [this, idx]() {
				auto it = FindInVector(m_Blocks, idx);
				if (it != m_Blocks.end())
				{
					return it->second->IsBreaking();
				}
				return false;
			};

		if (idx > static_cast<int>(m_GridPtr->size() - 1) || idx < 0)
		{
			return currentPos;
		}


		if (m_GridPtr->at(idx) == Tile::Empty || (isBlock && blockBreakingCheck()))
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
				auto args = WallShakeArgs{ Walls::Left };
				GetOwner()->NotifyObservers(Event{ make_sdbm_hash("WallShake") , &args });
				m_Walls->ShakeWall(Walls::Left);
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
				auto args = WallShakeArgs{ Walls::Right };
				GetOwner()->NotifyObservers(Event{ make_sdbm_hash("WallShake") , &args });
				m_Walls->ShakeWall(Walls::Right);
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
				auto args = WallShakeArgs{ Walls::Up };
				GetOwner()->NotifyObservers(Event{ make_sdbm_hash("WallShake") , &args });
				m_Walls->ShakeWall(Walls::Up);
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
				auto args = WallShakeArgs{ Walls::Down };
				GetOwner()->NotifyObservers(Event{ make_sdbm_hash("WallShake") , &args});
				m_Walls->ShakeWall(Walls::Down);
				return BlockState::Breaking;
			}
		}

		if (m_GridPtr->at(idx) != Tile::Empty)
		{
			if (idxBehind < 0 || idxBehind > static_cast<int>(m_GridPtr->size() - 1) ||		// out of range (push top and bottom blocks against edge)
				m_GridPtr->at(idxBehind) != Tile::Empty ||									// another block behind
				idx % WIDTH == 0 && direction.x < 0 ||										// pushing left against a block against the left wall
				idx % WIDTH == (WIDTH - 1) && direction.x > 0)								// pushing right against a block against the right wall
			{
				auto it = FindInVector(m_Blocks, idx);
				if (it != m_Blocks.end() && it->second->Destroy(true)) 
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

	BlockState GridComponent::RequestBreak(const glm::vec3& currentPos, const glm::vec3& direction)
	{
		int idx = PointToIdx(glm::vec3{ currentPos.x + (TILE_WIDTH / 2),currentPos.y + (TILE_WIDTH / 2),0 });
		if (direction.x < 0)
		{
			if (idx % WIDTH != 0)
			{
				--idx;
			}
		}
		if (direction.x > 0)
		{
			if (idx % WIDTH != (WIDTH - 1))
			{
				++idx;
			}
		}
		if (direction.y < 0)
		{
			if (idx / WIDTH != 0)
			{
				idx -= WIDTH;
			}
		}
		if (direction.y > 0)
		{
			if (idx / WIDTH != (HEIGHT - 1))
			{
				idx += WIDTH;
			}
		}

		if (idx < 0 || idx > static_cast<int>(m_GridPtr->size() - 1))
			return BlockState::Still;

		if (m_GridPtr->at(idx) != Tile::Unbreakable)
		{
			auto it = FindInVector(m_Blocks, idx);
			if (it != m_Blocks.end() && !it->second->IsSliding() && it->second->Destroy())
			{
				m_GridPtr->at(idx) = Tile::Empty;
				m_Blocks.erase(it);
				return BlockState::Breaking;
			}
		}

		return BlockState::Still;
	}

	std::vector<Tile>* GridComponent::GetGridLayout() const
	{
		return m_GridPtr.get();
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

	glm::vec3 GridComponent::PointToGridPos(const glm::vec3 position)
	{
		int idx = PointToIdx(position);
		return IdxToPoint(idx);
	}

	void GridComponent::RandomiseSnobee()
	{
		// Collect indices of all Breakable tiles
		std::vector<size_t> breakableIndices;
		for (size_t i = 0; i < m_GridPtr->size(); ++i)
		{
			if (m_GridPtr->at(i) == Tile::Breakable)
				breakableIndices.push_back(i);
		}

		// Shuffle the Breakable indices randomly
		std::random_device rd;
		std::mt19937 gen(rd());
		std::shuffle(breakableIndices.begin(), breakableIndices.end(), gen);

		// Set the first 'count' Breakable tiles to the new value
		for (int i = 0; i < 6; ++i)
		{
			m_GridPtr->at(breakableIndices[i]) = Tile::Sno_Bee;
		}
	}

	GridComponent::GridComponent(GameObject* owner, int width, int height, int tileWidth, glm::vec2 gridOfset, WallComponent* walls):
		CppBehaviour{ owner }, WIDTH {
		width
	}, HEIGHT{ height }, TILE_WIDTH{ tileWidth }, GRID_OFSETT{ gridOfset }, m_Walls{ walls }
	{
		m_GridPtr = std::make_unique<std::vector<Tile>>();
	}
}