#pragma once
#include "BaseCommand.h"
#include <memory>
#include "../Pengu/Enums.h"

namespace dae
{
    class GridComponent;
    class PengoComponent;
    class MoveCommand : public GameObjectCommand
    {
    public:
        MoveCommand(GameObject* gameObject, const glm::vec2& direction, GridComponent* grid, PengoComponent* pengo);
        void Execute() override;

    private:
        glm::vec2 m_Direction;
        GridComponent* m_Grid;
        PengoComponent* m_Pengo;
        PengoRotationState m_Rotation;
    };
}


