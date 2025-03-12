#pragma once
#include "Singleton.h"
#include "Windows.h"
#define WIN32_LEAN_AND_MEAN
#include <Xinput.h>
#pragma comment(lib, "Xinput.lib")
#include <memory>
#include "BaseCommand.h"

namespace dae
{
    class GameObjectCommand;

    class InputManager final : public Singleton<InputManager>
    {
        InputManager();
        ~InputManager();
        friend class Singleton<InputManager>;

        class inputImpl;
        std::unique_ptr<inputImpl> implPtr;

        std::vector<std::pair<unsigned int, std::unique_ptr<Command>>> m_commands;
    public:
        template <typename CommandType, typename... Args>
        void AddBinding(unsigned int button, InputType inputType, Args&&... args)
        {
            std::unique_ptr<Command> command = std::make_unique<CommandType>(std::forward<Args>(args)...);
            command->m_InputType = inputType;

            m_commands.emplace_back(button, std::move(command));
        }

        bool ProcessInput();
        //bool IsDownThisFrame(unsigned int button) const;
        //bool IsReleasedThisFrame(unsigned int button) const;
        //bool IsDown(unsigned int button) const;
    };
}
