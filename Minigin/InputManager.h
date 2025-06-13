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
        bool m_ClearedCommands = true;

        std::vector<std::pair<unsigned int, std::unique_ptr<Command>>> m_commands;
        std::vector<std::pair<unsigned int, std::unique_ptr<Command>>> m_commandsBuffer;
        std::vector<std::pair<unsigned int, std::unique_ptr<Command>>> m_globalCommands;
    public:
        template <typename CommandType, typename... Args>
        CommandType* AddBinding(unsigned int button, InputType inputType, int controllerIndex, Args&&... args)
        {
            std::unique_ptr<Command> command = std::make_unique<CommandType>(std::forward<Args>(args)...);
            command->m_InputType = inputType;
            command->m_ControllerIndex = controllerIndex;

            m_commandsBuffer.emplace_back(button, std::move(command));

            return static_cast<CommandType*>(m_commandsBuffer[m_commandsBuffer.size() - 1].second.get());
        }

        template <typename CommandType, typename... Args>
        CommandType* AddGlobalBinding(unsigned int button, InputType inputType, int controllerIndex, Args&&... args)
        {
            std::unique_ptr<Command> command = std::make_unique<CommandType>(std::forward<Args>(args)...);
            command->m_InputType = inputType;
            command->m_ControllerIndex = controllerIndex;

            m_globalCommands.emplace_back(button, std::move(command));

            return static_cast<CommandType*>(m_globalCommands[m_globalCommands.size() - 1].second.get());
        }

        bool ProcessInput();
        void ClearCommands();
    };
}
