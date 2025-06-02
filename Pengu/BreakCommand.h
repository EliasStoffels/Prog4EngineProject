#pragma once
#include "BaseCommand.h"
#include <memory>

namespace dae
{
    class EnemyComponent;
    class BreakCommand : public GameObjectCommand
    {
    public:
        BreakCommand(GameObject* gameObject, EnemyComponent* snobee);
        void Execute() override;

    private:
        EnemyComponent* m_SnobeePtr;
    };
}
