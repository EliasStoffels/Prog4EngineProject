#include "CppBehaviour.h"

dae::CppBehaviour::CppBehaviour()
{
}

void dae::CppBehaviour::Start()
{
}

void dae::CppBehaviour::Update([[maybe_unused]] float deltaTime)
{

}

void dae::CppBehaviour::FixedUpdate([[maybe_unused]] float fixedTime)
{
}

void dae::CppBehaviour::LateUpdate([[maybe_unused]] float deltaTime)
{
}

void dae::CppBehaviour::Render() const
{

}

void dae::CppBehaviour::SetOwningGameObject(GameObject* owningGameObject)
{
	m_OwningGameObject = owningGameObject;
}
