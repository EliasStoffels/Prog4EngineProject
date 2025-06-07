#include "CppBehaviour.h"

dae::CppBehaviour::CppBehaviour(GameObject* owner) : m_OwningGameObject{owner}
{
}

void dae::CppBehaviour::Start()
{
}

void dae::CppBehaviour::Update(float)
{

}

void dae::CppBehaviour::FixedUpdate(float)
{
}

void dae::CppBehaviour::LateUpdate(float)
{
}

void dae::CppBehaviour::Render() const
{

}

void dae::CppBehaviour::SetOwningGameObject(GameObject& owningGameObject)
{
	m_OwningGameObject = &owningGameObject;
}
