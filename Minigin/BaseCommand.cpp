#include "BaseCommand.h"

dae::GameObjectCommand::GameObjectCommand(GameObject* gameObject):
	m_gameObject{gameObject}
{
}

dae::GameObjectCommand::~GameObjectCommand()
{
}
