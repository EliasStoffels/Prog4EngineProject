#pragma once
#include "BaseCommand.h"
#include <memory>

namespace dae
{
    class EnemyControllerComponent;
    class BreakCommand : public GameObjectCommand
    {
    public:
        BreakCommand(GameObject* gameObject, EnemyControllerComponent* snobee);
        void Execute() override;

    private:
        EnemyControllerComponent* m_SnobeeControllerPtr;
    };
}
