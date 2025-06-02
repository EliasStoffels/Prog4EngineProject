#pragma once
#include "CppBehaviour.h"
#include "EnemyState.h"
#include <memory>
#include "glm.hpp"

namespace dae
{
    class TextureComponent;
    class GridComponent;
    class EnemyComponent : public CppBehaviour
    {
        friend class GameObject;
    public:

        void Start() override;
        void Update(float deltaTime) override;

        void Move(const glm::vec3& direction);
        void Break();

        // Getters for states
        TextureComponent* GetTexture() const { return m_TexturePtr; }
        float GetSpeed() const { return m_Speed; }
        glm::vec3 GetDirection() { return m_Direction; }
        GridComponent* GetGrid() const { return m_GridPtr; }

    private:
        EnemyComponent(float speed, GridComponent* grid);
        float m_Speed;
        GridComponent* m_GridPtr;
        TextureComponent* m_TexturePtr;
        glm::vec3 m_Direction{0,1,0};

        std::unique_ptr<EnemyState> m_CurrentState;
        void ChangeState(std::unique_ptr<EnemyState> newState);
    };
}

