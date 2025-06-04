#include <SDL.h>
#include "InputManager.h"
#include <algorithm>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>

namespace dae
{

    class InputManager::inputImpl 
    {
        //xinput
        static constexpr int MAX_CONTROLLERS = 4;

        struct ControllerState {
            XINPUT_STATE previousState{};
            XINPUT_STATE currentState{};
            int buttonChanges = 0;
            int buttonsPressedThisFrame = 0;
            int buttonsReleasedThisFrame = 0;
            bool isConnected = false;
        };

        ControllerState m_controllers[MAX_CONTROLLERS];

        //sdl
        const Uint8* currentKeyboardState = nullptr;
        Uint8 previousKeyboardState[SDL_NUM_SCANCODES] = { 0 };
    public:
        void ProcessInput(const  std::vector<std::pair<unsigned int, std::unique_ptr<Command>>>& commands);
        bool IsDownThisFrame(unsigned int button, int controllerIndex) const;
        bool IsReleasedThisFrame(unsigned int button, int controllerIndex) const;
        bool IsDown(unsigned int button, int controllerIndex) const;

        bool IsDownThisFrameKey(unsigned int key) const;
        bool IsReleasedThisFrameKey(unsigned int key) const;
        bool IsDownKey(unsigned int key) const;

        void CheckKeyboard(const std::pair<unsigned int, std::unique_ptr<Command>>& command);
        void CheckController(const std::pair<unsigned int, std::unique_ptr<Command>>& command);
    };

    void InputManager::inputImpl::ProcessInput(const std::vector<std::pair<unsigned int, std::unique_ptr<Command>>>& commands)
    {
        //update states
        //xinput
        for (int i = 0; i < MAX_CONTROLLERS; ++i)
        {
            auto& controller = m_controllers[i];
            CopyMemory(&controller.previousState, &controller.currentState, sizeof(XINPUT_STATE));
            ZeroMemory(&controller.currentState, sizeof(XINPUT_STATE));

            controller.isConnected = (XInputGetState(i, &controller.currentState) == ERROR_SUCCESS);
            if (controller.isConnected)
            {
                controller.buttonChanges = controller.currentState.Gamepad.wButtons ^ controller.previousState.Gamepad.wButtons;
                controller.buttonsPressedThisFrame = controller.buttonChanges & controller.currentState.Gamepad.wButtons;
                controller.buttonsReleasedThisFrame = controller.buttonChanges & (~controller.currentState.Gamepad.wButtons);
            }
        }

        // sdl
        SDL_PumpEvents();
        currentKeyboardState = SDL_GetKeyboardState(nullptr);

        //check commands
        std::for_each(commands.begin(), commands.end(), [this](const std::pair<unsigned int, std::unique_ptr<Command>>& command)
            {
                switch (command.second->m_InputType)
                {
                case InputType::Controller:
                {
                    CheckController(command);
                }
                break;
                case InputType::Keyboard:
                {
                    CheckKeyboard(command);
                }
                break;
                }
            });

        memcpy(previousKeyboardState, currentKeyboardState, SDL_NUM_SCANCODES);
    }

    bool dae::InputManager::inputImpl::IsDownThisFrame(unsigned int button, int controllerIndex) const
    {
        return m_controllers[controllerIndex].buttonsPressedThisFrame & button;
    }

    bool dae::InputManager::inputImpl::IsReleasedThisFrame(unsigned int button, int controllerIndex) const
    {
        return m_controllers[controllerIndex].buttonsReleasedThisFrame & button;
    }

    bool dae::InputManager::inputImpl::IsDown(unsigned int button, int controllerIndex) const
    {
        return m_controllers[controllerIndex].currentState.Gamepad.wButtons & button;
    }

    bool dae::InputManager::inputImpl::IsDownThisFrameKey(unsigned int key) const
    {
        return currentKeyboardState[key] && !previousKeyboardState[key];
    }

    bool dae::InputManager::inputImpl::IsReleasedThisFrameKey(unsigned int key) const
    {
        return !currentKeyboardState[key] && previousKeyboardState[key];
    }

    bool dae::InputManager::inputImpl::IsDownKey(unsigned int key) const
    {
        return currentKeyboardState[key];
    }

    void InputManager::inputImpl::CheckController(const std::pair<unsigned int, std::unique_ptr<Command>>& command)
    {

        if (IsDownThisFrame(command.first, command.second->m_ControllerIndex))
        {
            command.second->m_buttonState.PressedThisFrame = true;
            command.second->m_buttonState.Down = true;
            command.second->m_buttonState.ReleasedThisFrame = false;
            command.second->Execute();
        }
        else if (IsReleasedThisFrame(command.first, command.second->m_ControllerIndex))
        {
            command.second->m_buttonState.ReleasedThisFrame = true;
            command.second->m_buttonState.PressedThisFrame = false;
            command.second->m_buttonState.Down = false;
            command.second->Execute();
        }
        else if (IsDown(command.first, command.second->m_ControllerIndex))
        {
            command.second->m_buttonState.Down = true;
            command.second->m_buttonState.PressedThisFrame = false;
            command.second->m_buttonState.ReleasedThisFrame = false;
            command.second->Execute();
        }
        else
        {
            command.second->m_buttonState.Down = false;
            command.second->m_buttonState.PressedThisFrame = false;
            command.second->m_buttonState.ReleasedThisFrame = false;
        }
    }

    void dae::InputManager::inputImpl::CheckKeyboard(const std::pair<unsigned int, std::unique_ptr<Command>>& command)
    {
        SDL_Scancode key = static_cast<SDL_Scancode>(command.first);

        if (IsDownThisFrameKey(key))
        {
            command.second->m_buttonState.PressedThisFrame = true;
            command.second->m_buttonState.Down = true;
            command.second->m_buttonState.ReleasedThisFrame = false;
            command.second->Execute();
        }
        else if (IsReleasedThisFrameKey(key))
        {
            command.second->m_buttonState.ReleasedThisFrame = true;
            command.second->m_buttonState.PressedThisFrame = false;
            command.second->m_buttonState.Down = false;
            command.second->Execute();
        }
        else if (IsDownKey(key))
        {
            command.second->m_buttonState.Down = true;
            command.second->m_buttonState.PressedThisFrame = false;
            command.second->m_buttonState.ReleasedThisFrame = false;
            command.second->Execute();
        }
        else
        {
            command.second->m_buttonState.Down = false;
            command.second->m_buttonState.PressedThisFrame = false;
            command.second->m_buttonState.ReleasedThisFrame = false;
        }
    }
}
