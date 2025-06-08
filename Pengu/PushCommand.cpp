#include "PushCommand.h"

namespace dae
{
	PushCommand::PushCommand(PengoComponent* pengo)
		: m_PengoPtr{pengo}
	{
	}
	void PushCommand::Execute()
	{
		if(m_buttonState.PressedThisFrame)
			m_PengoPtr->Push();
	}
}

