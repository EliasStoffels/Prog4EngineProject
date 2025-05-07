#pragma once
#include "BaseCommand.h"
#include <memory>
#include "../Pengu/PengoComponent.h"


namespace dae
{

    class PushCommand : public GameObjectCommand
    {
    public:
        PushCommand(GameObject* gameObject, PengoComponent* pengo);
        void Execute() override;

    private:
        PengoComponent* m_PengoPtr;
    };
}

