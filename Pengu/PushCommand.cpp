#include "PushCommand.h"

namespace dae
{
	PushCommand::PushCommand(GameObject* gameObject, PengoComponent* pengo)
		: GameObjectCommand{ gameObject },m_PengoPtr{pengo}
	{
	}
	void PushCommand::Execute()
	{
		m_PengoPtr->Push();
	}
}

