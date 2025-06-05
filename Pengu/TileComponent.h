#pragma once
#include "CppBehaviour.h"
#include <glm.hpp>
#include "TextureComponent.h"
#include "Enums.h"
#include "GridComponent.h"

namespace dae
{
	

	class TileComponent : public CppBehaviour
	{
		friend class GameObject;
	public:
		void Start() override;
		void Slide(const glm::vec3& direction);
		bool Destroy();
		bool IsSliding();
		bool IsBreaking();

		void Update(float elapsedSec) override;

		virtual ~TileComponent() = default;
		TileComponent(const TileComponent& other) = delete;
		TileComponent(TileComponent&& other) = delete;
		TileComponent& operator=(const TileComponent& other) = delete;
		TileComponent& operator=(TileComponent&& other) = delete;

	private:
		TileComponent(Tile tileType, float x, float y,  GridComponent* grid);
		// sliding
		GridComponent* m_GridPtr = nullptr;
		glm::vec3 m_TargetPosition{FLT_MAX,FLT_MAX,0};
		float m_SlideSpeed;
		// blockType
		TextureComponent* m_Texture = nullptr;
		Tile m_TileType;

		// animate 
		const float FRAME_DELAY;
		float m_TotalDT = 0.f;
		int m_CurrentFrame = 0;

		// blockState 
		BlockState m_BlockState;
		glm::vec3 m_Pos;
		glm::vec3 m_SlideDirection{};
	};
}