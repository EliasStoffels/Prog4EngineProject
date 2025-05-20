#pragma once
#include "GameObject.h"

namespace dae
{
	enum class InputType
	{
		Controller,
		Keyboard
	};

	struct ButtonState
	{
		bool PressedThisFrame = false;
		bool ReleasedThisFrame = false;
		bool Down = false;
	};

	class Command
	{
	public:
		ButtonState m_buttonState;
		InputType m_InputType;
		int m_ControllerIndex = 0;

		virtual ~Command() = default;
		virtual void Execute() = 0;
	};

	class GameObjectCommand : public Command
	{
		GameObject* m_gameObject;
	protected:
		GameObject* GetGameObject() const { return m_gameObject; };
	public:
		GameObjectCommand(GameObject* gameObject);
		virtual ~GameObjectCommand();
	};
}

