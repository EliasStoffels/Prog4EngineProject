#pragma once
#include "Singleton.h"
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
        void AddBinding(unsigned int button, InputType inputType, int controllerIndex, Args&&... args)
        {
            std::unique_ptr<Command> command = std::make_unique<CommandType>(std::forward<Args>(args)...);
            command->m_InputType = inputType;
            command->m_ControllerIndex = controllerIndex;

            m_commands.emplace_back(button, std::move(command));
        }

        bool ProcessInput();
        void ClearCommands();
    };
}
