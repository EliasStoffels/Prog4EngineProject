#include <SDL.h>
#include "InputManager.h"
#include <iostream>
#include "GameObject.h"
#include <algorithm>

namespace dae
{
    class dae::InputManager::inputImpl
    {
        //xinput
        XINPUT_STATE previousState{};
        XINPUT_STATE currentState{};
        int m_controllerIndex = 0;

        int buttonChanges = 0;
        int buttonsPressedThisFrame = 0;
        int buttonsReleasedThisFrame = 0;

        //sdl
        const Uint8* currentKeyboardState = nullptr;
        Uint8 previousKeyboardState[SDL_NUM_SCANCODES] = { 0 }; // Stores previous frame's state


    public:
        void ProcessInput(const  std::vector<std::pair<unsigned int, std::unique_ptr<Command>>>& commands);
        bool IsDownThisFrame(unsigned int button) const;
        bool IsReleasedThisFrame(unsigned int button) const;
        bool IsDown(unsigned int button) const;

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
        CopyMemory(&previousState, &currentState, sizeof(XINPUT_STATE));
        ZeroMemory(&currentState, sizeof(XINPUT_STATE));
        XInputGetState(m_controllerIndex, &currentState);
        buttonChanges = currentState.Gamepad.wButtons ^ previousState.Gamepad.wButtons;
        buttonsPressedThisFrame = buttonChanges & currentState.Gamepad.wButtons;
        buttonsReleasedThisFrame = buttonChanges & (~currentState.Gamepad.wButtons);

        // sdl
        if(currentKeyboardState != nullptr)
        memcpy(previousKeyboardState, currentKeyboardState, SDL_NUM_SCANCODES);
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
                case InputType::Both:
                    {
                        CheckKeyboard(command);
                        CheckController(command);
                    }
                    break;
                }
            });
    }

    bool InputManager::inputImpl::IsDownThisFrame(unsigned int button) const
    {
        return buttonsPressedThisFrame & button;
    }

    bool InputManager::inputImpl::IsReleasedThisFrame(unsigned int button) const
    {
        return buttonsReleasedThisFrame & button;
    }

    bool InputManager::inputImpl::IsDown(unsigned int button) const
    {
        return currentState.Gamepad.wButtons & button;
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

    void dae::InputManager::inputImpl::CheckController(const std::pair<unsigned int, std::unique_ptr<Command>>& command)
    {
        if (IsDownThisFrame(command.first))
        {
            command.second->m_buttonState.PressedThisFrame = true;
            command.second->m_buttonState.Down = true;
            command.second->m_buttonState.ReleasedThisFrame = false;
            command.second->Execute();
        }
        else if (IsReleasedThisFrame(command.first))
        {
            command.second->m_buttonState.ReleasedThisFrame = true;
            command.second->m_buttonState.PressedThisFrame = false;
            command.second->m_buttonState.Down = false;
            command.second->Execute();
        }
        else if (IsDown(command.first))
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

    bool InputManager::ProcessInput()
    {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                return false;
            }
            if (e.type == SDL_KEYDOWN) {
            }
        }

        implPtr->ProcessInput(m_commands);
        return true;
    }

    //bool InputManager::IsDownThisFrame(unsigned int button) const
    //{
    //    return implPtr->IsDownThisFrame(button);
    //}
    //
    //bool InputManager::IsReleasedThisFrame(unsigned int button) const
    //{
    //    return implPtr->IsReleasedThisFrame(button);
    //}
    //
    //bool InputManager::IsDown(unsigned int button) const
    //{
    //    return implPtr->IsDown(button);
    //}

    InputManager::InputManager()
        : implPtr(std::make_unique<inputImpl>())
    {
    }

    InputManager::~InputManager()
    {
    }
}
