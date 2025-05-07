#pragma once
#include "glm.hpp"

namespace dae
{
	enum class Tile:uint8_t
	{
		Empty, Breakable, Unbreakable
	};

	enum class PengoRotationState:uint8_t
	{
		Left, Right, Up, Down
	};

	glm::vec2 RotationToVec2(const PengoRotationState& rotation);
	

	glm::vec3 RotationToVec3(const PengoRotationState& rotation);


	PengoRotationState VecToRotation(const glm::vec2 vec);
	

	PengoRotationState VecToRotation(const glm::vec3 vec);
	

	enum class PengoAnimationState:uint8_t
	{
		Walking, Pushing, Dying
	};
}