#pragma once
#include "CppBehaviour.h"
#include <glm.hpp>
#include <TextureComponent.h>
#include "Enums.h"

namespace dae
{
	

	class TileComponent : public CppBehaviour
	{
		friend class GameObject;

	public:
		void Slide(const glm::vec2& direction);

		void Update(float elapsedSec) override;

		virtual ~TileComponent() = default;
		TileComponent(const TileComponent& other) = delete;
		TileComponent(TileComponent&& other) = delete;
		TileComponent& operator=(const TileComponent& other) = delete;
		TileComponent& operator=(TileComponent&& other) = delete;

	private:
		TileComponent(const Tile& tileType, float x, float y, float tileSize);
		const float TILE_SIZE;

		TextureComponent* m_Texture = nullptr;
		Tile m_TileType;
		bool tileSet = false;
		glm::vec2 m_Pos;
	};
}