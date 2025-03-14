#pragma once
#include "BaseCommand.h"
#include <memory>
#include "ScoreComponent.h"

namespace dae
{
    class KillEnemyCommand : public GameObjectCommand
    {
    public:
        KillEnemyCommand(GameObject* gameObject);
        void Execute() override;

    private:
        ScoreComponent* m_ScoreComponent = nullptr;
    };
}