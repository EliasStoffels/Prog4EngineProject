#include <SDL.h>
#include "InputManager.h"

#include "windows.h"
#define WIN32_LEAN_AND_MEAN
#include <Xinput.h>

namespace dae
{
    class dae::InputManager::inputImpl
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

    InputManager::InputManager()
        : implPtr(std::make_unique<inputImpl>())
    {
    }

    InputManager::~InputManager()
    {
    }

    void InputManager::ClearCommands()
    {
        m_commands.clear();
    }
}
