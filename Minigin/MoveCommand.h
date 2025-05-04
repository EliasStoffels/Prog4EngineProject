#pragma once
#include "BaseCommand.h"
#include <memory>

namespace dae
{

    class MoveCommand : public GameObjectCommand
    {
    public:
        MoveCommand(GameObject* gameObject, float speed,glm::vec2 direction);
        void Execute() override;

    private:
        float m_Speed;
        glm::vec2 m_Direction;

    };
}


