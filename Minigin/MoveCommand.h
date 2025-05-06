#pragma once
#include "BaseCommand.h"
#include <memory>
#include "../Pengu/GridComponent.h"
#include "../Pengu/PengoComponent.h"


namespace dae
{

    class MoveCommand : public GameObjectCommand
    {
    public:
        MoveCommand(GameObject* gameObject, float speed, const glm::vec2& direction, GridComponent* grid, PengoComponent* pengo);
        void Execute() override;

    private:
        float m_Speed;
        glm::vec2 m_Direction;
        GridComponent* m_Grid;
        PengoComponent* m_Pengo;
    };
}


