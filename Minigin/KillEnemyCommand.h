#pragma once
#include "BaseCommand.h"
#include <memory>
#include "HealthComponent.h"

namespace dae
{
    class KillEnemyCommand : public GameObjectCommand
    {
    public:
        KillEnemyCommand(GameObject* gameObject);
        void Execute() override;

    private:
    };
}