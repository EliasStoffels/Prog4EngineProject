#pragma once
#include "BaseCommand.h"
#include <memory>
#include "../Pengu/Enums.h"
#include "../Pengu/PengoComponent.h"
#include "../Pengu/EnemyControllerComponent.h"
#include "GameObject.h"

namespace dae
{
    class GridComponent;
    class PengoComponent;

    template <typename T>
    class MoveCommand : public Command
    {
    public:
        template <typename T>
        MoveCommand(const glm::vec3& direction, T* character) : m_Direction{ direction }, m_Character{ character } {}
        void Execute() override
        {
            m_Character->Move(m_Direction);
        }

    private:
        glm::vec3 m_Direction;
        T* m_Character;
    };
}


