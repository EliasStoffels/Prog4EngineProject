#pragma once
#include "glm.hpp"

namespace dae
{
	class TileComponent;
	struct TileMoveArg
	{
		TileComponent* tile;
		glm::vec3 position;
		glm::vec3 direction;
	};

	struct ScoreChangedArgs
	{
		int amount;
	};

}
