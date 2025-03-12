#pragma once
#include "BaseCommand.h"
#include <memory>

namespace dae
{
    enum class Direction
    {
        Up,
        Down,
        Left,
        Right
    };

    class MoveCommand : public GameObjectCommand
    {
    public:
        MoveCommand(GameObject* gameObject, float speed, Direction direction);
        void Execute() override;

    private:
        float m_Speed;
        Direction m_Direction;
    };
}


