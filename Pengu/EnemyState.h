#pragma once
#include "glm.hpp"
#include <memory>
#include "GameStateManager.h"
#include "enums.h"

namespace dae
{

    class TextureComponent;
    class EnemyComponent;
    class GameObject;
    class EnemyState
    {
    protected:
        TextureComponent* m_TexturePtr = nullptr;
        glm::vec3 m_Direction{};
        float m_TotalDT{};
        float FRAME_DELAY{ 0.15f };
        int m_CurrentFrame{ 0 };
        const IntVec2 LVL_TEXTURE_OFSETT{GameStateManager::GetInstance().GetLevel() * 128, 128};

    public:
        virtual ~EnemyState() = default;
        virtual void Enter(EnemyComponent* snobee) = 0;
        virtual std::unique_ptr<EnemyState> Update(EnemyComponent* snobee, float deltaTime) = 0;
        virtual void Animate(EnemyComponent* snobee, float deltaTime) = 0;
        virtual void Exit(EnemyComponent* snobee) = 0;

        virtual std::unique_ptr<EnemyState> OnMove(EnemyComponent* snobee) = 0;
        virtual std::unique_ptr<EnemyState> Break(EnemyComponent* snobee) = 0;
        virtual std::unique_ptr<EnemyState> GetHit(EnemyComponent* snobee, GameObject* block) = 0;
        virtual std::unique_ptr<EnemyState> Reset(EnemyComponent* snobee, int) = 0;
    };

    class EnemySpawningState : public EnemyState
    {
        glm::vec3 m_TargetPosition{ FLT_MAX,FLT_MAX,FLT_MAX };
    public:
        void Enter(EnemyComponent* snobee) override;
        std::unique_ptr<EnemyState> Update(EnemyComponent* snobee, float deltaTime) override;
        void Animate(EnemyComponent* snobee, float deltaTime) override;
        void Exit(EnemyComponent* snobee) override;

        std::unique_ptr<EnemyState> OnMove(EnemyComponent* pengo) override;
        std::unique_ptr<EnemyState> Break(EnemyComponent* pengo) override;
        std::unique_ptr<EnemyState> GetHit(EnemyComponent* snobee, GameObject* block) override;
        std::unique_ptr<EnemyState> Reset(EnemyComponent* snobee, int) override;
    };

    class EnemyWalkingState : public EnemyState
    {
        glm::vec3 m_TargetPosition{ FLT_MAX,FLT_MAX,FLT_MAX };
    public:
        void Enter(EnemyComponent* snobee) override;
        std::unique_ptr<EnemyState> Update(EnemyComponent* snobee, float deltaTime) override;
        void Animate(EnemyComponent* snobee, float deltaTime) override;
        void Exit(EnemyComponent* snobee) override;

        std::unique_ptr<EnemyState> OnMove(EnemyComponent* pengo) override;
        std::unique_ptr<EnemyState> Break(EnemyComponent* pengo) override;
        std::unique_ptr<EnemyState> GetHit(EnemyComponent* snobee, GameObject* block) override;
        std::unique_ptr<EnemyState> Reset(EnemyComponent* snobee, int) override;



    };

    class EnemyBreakingState : public EnemyState
    {
        glm::vec3 m_TargetPosition{ FLT_MAX,FLT_MAX,FLT_MAX };
    public:
        void Enter(EnemyComponent* snobee) override;
        std::unique_ptr<EnemyState> Update(EnemyComponent* snobee, float deltaTime) override;
        void Animate(EnemyComponent* snobee, float deltaTime) override;
        void Exit(EnemyComponent* snobee) override;

        std::unique_ptr<EnemyState> OnMove(EnemyComponent* snobee) override;
        std::unique_ptr<EnemyState> Break(EnemyComponent* snobee) override;        
        std::unique_ptr<EnemyState> GetHit(EnemyComponent* snobee, GameObject* block) override;
        std::unique_ptr<EnemyState> Reset(EnemyComponent* snobee, int) override;

    private:
    };

    class EnemyStunnedState : public EnemyState
    {
        glm::vec3 m_TargetPosition{ FLT_MAX,FLT_MAX,FLT_MAX };
    public:
        void Enter(EnemyComponent* snobee) override;
        std::unique_ptr<EnemyState> Update(EnemyComponent* snobee, float deltaTime) override;
        void Animate(EnemyComponent* snobee, float deltaTime) override;
        void Exit(EnemyComponent* snobee) override;

        std::unique_ptr<EnemyState> OnMove(EnemyComponent* snobee) override;
        std::unique_ptr<EnemyState> Break(EnemyComponent* snobee) override;
        std::unique_ptr<EnemyState> GetHit(EnemyComponent* snobee, GameObject* block) override;
        std::unique_ptr<EnemyState> Reset(EnemyComponent* snobee, int) override;
    private:
    };

    class TileComponent;
    class EnemySlidingState : public EnemyState
    {
        glm::vec3 m_TargetPosition{ FLT_MAX,FLT_MAX,FLT_MAX };
        TileComponent* m_TilePtr = nullptr;
    public:
        void Enter(EnemyComponent* snobee) override;
        std::unique_ptr<EnemyState> Update(EnemyComponent* snobee, float deltaTime) override;
        void Animate(EnemyComponent* snobee, float deltaTime) override;
        void Exit(EnemyComponent* snobee) override;

        std::unique_ptr<EnemyState> OnMove(EnemyComponent* snobee) override;
        std::unique_ptr<EnemyState> Break(EnemyComponent* snobee) override;
        std::unique_ptr<EnemyState> GetHit(EnemyComponent* snobee, GameObject* block) override;
        std::unique_ptr<EnemyState> Reset(EnemyComponent* snobee, int) override;

    private:
        bool m_IsDead = false;
    };
}

