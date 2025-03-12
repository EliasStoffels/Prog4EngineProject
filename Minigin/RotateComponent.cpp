#include "RotateComponent.h"
#include "GameObject.h"
#include <SDL_stdinc.h>
#include <iostream>

dae::RotateComponent::RotateComponent()
{
}

void dae::RotateComponent::Update(float deltaTime)
{
	m_totalDeltaTime += deltaTime;
	
	m_OwningGameObject->SetLocalPosition(m_radius * cos(m_radianPerSecond * m_totalDeltaTime), m_radius * sin(m_radianPerSecond * m_totalDeltaTime));
}

void dae::RotateComponent::SetRadius(float radius)
{
	m_radius = radius;
}

void dae::RotateComponent::SetRadianPerSecond(float radianPerSecond)
{
	m_radianPerSecond = radianPerSecond;
}

void dae::RotateComponent::SetDegreePerSecond(float degreePerSecond)
{
	m_radianPerSecond = degreePerSecond / 180 * static_cast<float>(M_PI);
}
