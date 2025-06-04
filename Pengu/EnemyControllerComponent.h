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
    class PengoComponent;
    class EnemyControllerComponent : public CppBehaviour
    {
        friend class GameObject;
    public:

        void Start() override;
        void Update(float deltaTime) override;

        void SpawnEnemy(const glm::vec2& position);
        void AddPengo(PengoComponent* pengo);

        void Move(const glm::vec3 direction);
        void Break();
        void PlayerControlled(bool playerControlled);

    private:
        EnemyControllerComponent(GridComponent* grid);
        static constexpr int TILE_WIDTH = 48;
        static constexpr int MAXIMUM_SNOBEES = 3;

        std::vector<EnemyComponent*> m_Snobees;
        std::vector<Tile>* m_GridLayoutPtr = nullptr;
        GridComponent* m_GridPtr;
        std::vector<PengoComponent*> m_PengosPtr;
        int m_SnobeeTargetPosIdx[MAXIMUM_SNOBEES]{};
        int m_AttackingSnobees = 0;
        int m_NextAttackingSnobees = 0;
        bool m_PlayerControlled = false;
        int m_SnobeesAlive = 0;
        int m_SnobeesDead = 0;

        float m_TotalDT = 0.f;
        float m_AttackInterval = 10.f;

        int m_ControlledSnobee = 0;

    };
}

