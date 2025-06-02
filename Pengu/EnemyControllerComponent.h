#pragma once
#include "CppBehaviour.h"
#include "glm.hpp"
#include <vector>
#include "enums.h"

namespace dae
{
    class TextureComponent;
    class GridComponent;
    class EnemyComponent;
    class EnemyControllerComponent : public CppBehaviour
    {
        friend class GameObject;
    public:

        void Start() override;
        void Update(float deltaTime) override;

        void SpawnEnemy(const glm::vec2& position);

    private:
        EnemyControllerComponent(GridComponent* grid);
        const int TILE_WIDTH = 48;
        const int  MAXIMUM_SNOBEES = 3;

        std::vector<EnemyComponent*> m_Snobees;
        std::vector<Tile>* m_GridLayout = nullptr;
        GridComponent* m_GridPtr;
        bool m_PlayerControlled = false;
        int m_SnobeesAlive = 0;
    };
}

