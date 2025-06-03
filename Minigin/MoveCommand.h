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
    class MoveCommand : public GameObjectCommand
    {
    public:
        template <typename T>
        MoveCommand(GameObject* gameObject, const glm::vec3& direction, T* character) : GameObjectCommand{ gameObject }, m_Direction{ direction }, m_Character{ character } {}
        void Execute() override
        {
            m_Character->Move(m_Direction);
        }

    private:
        glm::vec3 m_Direction;
        T* m_Character;
    };
}


