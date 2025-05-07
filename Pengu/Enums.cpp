#include "Enums.h"

namespace dae
{
	glm::vec2 RotationToVec2(const PengoRotationState& rotation)
	{
		switch (rotation)
		{
		case PengoRotationState::Left:
			return glm::vec2{ -1,0 };
			break;
		case PengoRotationState::Right:
			return glm::vec2{ 1,0 };
			break;
		case PengoRotationState::Up:
			return glm::vec2{ 0,1 };
			break;
		case PengoRotationState::Down:
			return glm::vec2{ 0,-1 };
			break;
		}
	
		return glm::vec2{ 0,1 };
	}

	glm::vec3 RotationToVec3(const PengoRotationState& rotation)
	{
		switch (rotation)
		{
		case PengoRotationState::Left:
			return glm::vec3{ -1,0,0 };
			break;
		case PengoRotationState::Right:
			return glm::vec3{ 1,0,0 };
			break;
		case PengoRotationState::Up:
			return glm::vec3{ 0,1,0 };
			break;
		case PengoRotationState::Down:
			return glm::vec3{ 0,-1,0 };
			break;
		}

		return glm::vec3{ 0,1,0 };
	}

	PengoRotationState VecToRotation(const glm::vec2 vec)
	{
		if (vec.x < 0)
		{
			return PengoRotationState::Left;
		}
		if (vec.x > 0)
		{
			return PengoRotationState::Right;
		}
		if (vec.y < 0)
		{
			return PengoRotationState::Down;
		}
		if (vec.y > 0)
		{
			return PengoRotationState::Up;
		}

		return PengoRotationState::Up;
	}

	PengoRotationState VecToRotation(const glm::vec3 vec)
	{
		if (vec.x < 0)
		{
			return PengoRotationState::Left;
		}
		if (vec.x > 0)
		{
			return PengoRotationState::Right;
		}
		if (vec.y < 0)
		{
			return PengoRotationState::Down;
		}
		if (vec.y > 0)
		{
			return PengoRotationState::Up;
		}

		return PengoRotationState::Up;
	}

}
