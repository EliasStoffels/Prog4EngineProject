#pragma once
#include "glm.hpp"
#include <memory>

namespace dae
{
    class TextureComponent;
    class EnemyComponent;
    class EnemyState
    {
    protected:
        TextureComponent* m_TexturePtr = nullptr;
        glm::vec3 m_Direction{};
        float m_TotalDT{};
        float FRAME_DELAY{ 0.1f };
        int m_CurrentFrame{ 0 };

    public:
        virtual ~EnemyState() = default;
        virtual void Enter(EnemyComponent* snobee) = 0;
        virtual std::unique_ptr<EnemyState> Update(EnemyComponent* snobee, float deltaTime) = 0;
        virtual void Animate(EnemyComponent* snobee, float deltaTime) = 0;
        virtual void Exit(EnemyComponent* snobee) = 0;
    };

    class EnemyWalkingState : public EnemyState
    {
        glm::vec3 m_TargetPosition{ FLT_MAX,FLT_MAX,FLT_MAX };
    public:
        void Enter(EnemyComponent* snobee) override;
        std::unique_ptr<EnemyState> Update(EnemyComponent* snobee, float deltaTime) override;
        void Animate(EnemyComponent* snobee, float deltaTime) override;
        void Exit(EnemyComponent* snobee) override;
    };
}

