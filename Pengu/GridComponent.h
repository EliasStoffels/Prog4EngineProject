#pragma once
#include "CppBehaviour.h"
#include <vector>
#include <glm.hpp>
#include <memory>
#include "Enums.h"

namespace dae
{
	class WallComponent;
	class TextureComponent;
	class TileComponent;
	class GridComponent : public CppBehaviour
	{
		friend class GameObject;

	public:
		void SaveLevel();
		void LoadLevel(int level);
		glm::vec3 RequestMove(const glm::vec3& currentPos, glm::vec3& direction, bool isBlock =false);
		BlockState RequestPush(const glm::vec3& currentPos, const glm::vec3& direction);
		BlockState RequestBreak(const glm::vec3& currentPos, const glm::vec3& direction);
		std::vector<Tile>* GetGridLayout() const;
		int PointToIdx(const glm::vec3 position);
		glm::vec3 IdxToPoint(int idx);
		void RandomiseSnobee();

		virtual ~GridComponent() = default;
		GridComponent(const GridComponent& other) = delete;
		GridComponent(GridComponent&& other) = delete;
		GridComponent& operator=(const GridComponent& other) = delete;
		GridComponent& operator=(GridComponent&& other) = delete;

	private:
		GridComponent(int width, int height, int tileWidth, glm::vec2 gridOfset, WallComponent* walls);
		const int WIDTH;
		const int HEIGHT;
		const int TILE_WIDTH;
		const glm::vec2 GRID_OFSETT;

		std::unique_ptr<std::vector<Tile>> m_GridPtr = nullptr;
		std::vector<std::pair<int, TileComponent*>> m_Blocks;

		WallComponent* m_Walls = nullptr;

	};
}

