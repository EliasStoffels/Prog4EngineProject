#pragma once
#include "CppBehaviour.h"
#include <vector>
#include <glm.hpp>
#include <memory>
#include "Enums.h"

namespace dae
{

	class GridComponent : public CppBehaviour
	{
		friend class GameObject;

	public:
		void SaveLevel();
		void LoadLevel(int level);
		bool RequestMove(float x, float y);

		virtual ~GridComponent() = default;
		GridComponent(const GridComponent& other) = delete;
		GridComponent(GridComponent&& other) = delete;
		GridComponent& operator=(const GridComponent& other) = delete;
		GridComponent& operator=(GridComponent&& other) = delete;

	private:
		GridComponent(int width, int height, int tileWidth, glm::vec2 gridOfset);
		const int WIDTH;
		const int HEIGHT;
		const int TILE_WIDTH;
		const glm::vec2 GRID_OFSETT;

		std::unique_ptr<std::vector<Tile>> m_GridPtr = nullptr;
		GameObject* m_Pengo = nullptr;


	};
}

