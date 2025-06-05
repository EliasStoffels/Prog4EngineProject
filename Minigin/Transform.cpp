#include "Transform.h"
#include "GameObject.h"
#include <algorithm>
#include "TimeSingleton.h"

const glm::vec3& dae::Transform::GetLocalPosition() const
{
	return m_localPosition;
}

void dae::Transform::SetWorldPosition(float x, float y, float z)
{
	SetWorldPosition(glm::vec3{x,y,z});
}

void dae::Transform::SetWorldPosition(glm::vec3 pos)
{
	auto parentPos = m_parent->GetWorldPosition();
	auto difference = pos - parentPos;
	SetLocalPosition(difference);
}

void dae::Transform::SetLocalPosition(const float x, const float y, const float z)
{
	m_localPosition.x = x;
	m_localPosition.y = y;
	m_localPosition.z = z;

	SetPositionDirty();
}

void dae::Transform::SetLocalPosition(glm::vec3 pos)
{
	m_localPosition.x = pos.x;
	m_localPosition.y = pos.y;
	m_localPosition.z = pos.z;

	SetPositionDirty();
}

dae::GameObject* dae::Transform::GetParent()
{
	return m_parent;
}

const glm::vec3& dae::Transform::GetWorldPosition()
{
	if (m_positionDirty)
	{
		UpdatePosition();
	}
	return m_worldPosition;
}


void dae::Transform::Move(glm::vec3 direction)
{
	SetLocalPosition(m_localPosition + direction);
}

void dae::Transform::UpdatePosition()
{
	if (m_positionDirty)
	{
		if (m_parent == nullptr)
			m_worldPosition = m_localPosition;
		else
		m_worldPosition = m_parent->GetTransform()->GetWorldPosition() + m_localPosition;
	}
	m_positionDirty = false;
}

void dae::Transform::SetPositionDirty()
{
	m_positionDirty = true;
	 
	if(m_childObjects)
		std::for_each(m_childObjects->begin(), m_childObjects->end(), [](dae::GameObject* child) {child->GetTransform()->SetPositionDirty();});
}

