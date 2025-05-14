#pragma once
#include "glm.hpp"

namespace dae
{
	enum class Tile:uint8_t
	{
		Empty, Breakable, Unbreakable
	};

	enum class DirectionState:uint8_t
	{
		Left, Right, Up, Down
	};

	glm::vec2 RotationToVec2(const DirectionState& rotation);

	glm::vec3 RotationToVec3(const DirectionState& rotation);

	DirectionState VecToRotation(const glm::vec2 vec);

	DirectionState VecToRotation(const glm::vec3 vec);

	enum class PengoActionState:uint8_t
	{
		Walking, Pushing, Dying
	};

	enum class BlockState : uint8_t
	{
		Still, Sliding, Breaking
	};
}