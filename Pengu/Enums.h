#pragma once
#include "glm.hpp"

namespace dae
{
	enum class Tile:uint8_t
	{
		Empty, Breakable, Unbreakable, Sno_Bee
	};

	enum class Walls:uint8_t
	{
		Left, Right, Up, Down
	};

	enum class BlockState : uint8_t
	{
		Still, Sliding, Breaking, Spawning
	};
}