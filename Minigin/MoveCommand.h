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
        MoveCommand(GameObject* gameObject, const glm::vec3& direction, PengoComponent* pengo);
        void Execute() override;

    private:
        glm::vec3 m_Direction;
        PengoComponent* m_Pengo;
    };
}


