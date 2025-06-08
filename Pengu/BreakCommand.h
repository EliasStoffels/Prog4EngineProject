#pragma once
#include "BaseCommand.h"
#include <memory>

namespace dae
{
    class EnemyControllerComponent;
    class BreakCommand : public Command
    {
    public:
        BreakCommand(EnemyControllerComponent* snobee);
        void Execute() override;

    private:
        EnemyControllerComponent* m_SnobeeControllerPtr;
    };
}
