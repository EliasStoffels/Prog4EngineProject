#pragma once
#include "CppBehaviour.h"
#include "TextureComponent.h"
#include "Enums.h"

namespace dae
{
	class WallComponent : public CppBehaviour
	{
		friend class GameObject;
	public:
		void Update(float deltaTime) override;
		
		void ShakeWall(Walls direction);

		virtual ~WallComponent() = default;
		WallComponent(const WallComponent& other) = delete;
		WallComponent(WallComponent&& other) = delete;
		WallComponent& operator=(const WallComponent& other) = delete;
		WallComponent& operator=(WallComponent&& other) = delete;

	private:
		WallComponent(GameObject* owner, const glm::vec2& gridOfsett, const glm::vec2& gridSize, TextureComponent* vertWallTex, TextureComponent* horWallTex);
		TextureComponent* m_VertWallTex;
		TextureComponent* m_HorWallTex;

		const glm::vec2 GRID_OFSETT;
		const glm::vec2 GRID_SIZE;
		const float WALL_WIDTH = 25;

		float m_TotalDT = 0.f;
		float m_FrameDelay = 0.1f;

		const int FRAMES = 5;
		int m_Currentframe = 0;

		bool m_Shake = false;

	};
}