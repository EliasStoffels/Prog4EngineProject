#pragma once
#include "CppBehaviour.h"
#include <memory>
#include "glm.hpp"

namespace dae
{
    class TextComponent;
    class GameObject;
    class HighScoreNameComponent : public CppBehaviour
    {
        friend class GameObject;
    public:
       /* void Start() override;
        void Update(float deltaTime) override;*/

        void ChangeLetter(int idx, bool increase);

    private:
        HighScoreNameComponent(GameObject* owner);
        TextComponent* m_NameTexture;
        char m_Name[4] = "AAA";
    };
}

