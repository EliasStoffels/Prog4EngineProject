#pragma once
#include "BaseCommand.h"
#include <memory>
#include "../Pengu/PengoComponent.h"


namespace dae
{

    class PushCommand : public Command
    {
    public:
        PushCommand(PengoComponent* pengo);
        void Execute() override;

    private:
        PengoComponent* m_PengoPtr;
    };
}

