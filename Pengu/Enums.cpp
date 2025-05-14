#include "Enums.h"

namespace dae
{
	glm::vec2 RotationToVec2(const DirectionState& rotation)
	{
		switch (rotation)
		{
		case DirectionState::Left:
			return glm::vec2{ -1,0 };
			break;
		case DirectionState::Right:
			return glm::vec2{ 1,0 };
			break;
		case DirectionState::Up:
			return glm::vec2{ 0,1 };
			break;
		case DirectionState::Down:
			return glm::vec2{ 0,-1 };
			break;
		}
	
		return glm::vec2{ 0,1 };
	}

	glm::vec3 RotationToVec3(const DirectionState& rotation)
	{
		switch (rotation)
		{
		case DirectionState::Left:
			return glm::vec3{ -1,0,0 };
			break;
		case DirectionState::Right:
			return glm::vec3{ 1,0,0 };
			break;
		case DirectionState::Up:
			return glm::vec3{ 0,1,0 };
			break;
		case DirectionState::Down:
			return glm::vec3{ 0,-1,0 };
			break;
		}

		return glm::vec3{ 0,1,0 };
	}

	DirectionState VecToRotation(const glm::vec2 vec)
	{
		if (vec.x < 0)
		{
			return DirectionState::Left;
		}
		if (vec.x > 0)
		{
			return DirectionState::Right;
		}
		if (vec.y < 0)
		{
			return DirectionState::Down;
		}
		if (vec.y > 0)
		{
			return DirectionState::Up;
		}

		return DirectionState::Up;
	}

	DirectionState VecToRotation(const glm::vec3 vec)
	{
		if (vec.x < 0)
		{
			return DirectionState::Left;
		}
		if (vec.x > 0)
		{
			return DirectionState::Right;
		}
		if (vec.y < 0)
		{
			return DirectionState::Down;
		}
		if (vec.y > 0)
		{
			return DirectionState::Up;
		}

		return DirectionState::Up;
	}

}
