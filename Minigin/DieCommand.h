#pragma once
#include "BaseCommand.h"
#include <memory>
#include "HealthComponent.h"

namespace dae
{
    class DieCommand : public GameObjectCommand
    {
    public:
        DieCommand(GameObject* gameObject);
        void Execute() override;

    private:
        HealthComponent* m_HealthComponent;
    };
}