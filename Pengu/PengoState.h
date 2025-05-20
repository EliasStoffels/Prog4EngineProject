// PengoState.h
#pragma once
#include "GameObject.h"
#include "TimeSingleton.h"

namespace dae
{
    class TextureComponent;
    class PengoComponent;
    class PengoState
    {
    protected:
        TextureComponent* m_TexturePtr = nullptr;
        glm::vec3 m_Direction{};
        float m_TotalDT{};
        float FRAME_DELAY{ 0.1f };
        int m_CurrentFrame{ 0 };

    public:
        virtual ~PengoState() = default;
        virtual void Enter(PengoComponent* pengo) = 0;
        virtual std::unique_ptr<PengoState> Update(PengoComponent* pengo, float deltaTime) = 0;
        virtual void Animate(PengoComponent* pengo, float deltaTime) = 0;
        virtual void Exit(PengoComponent* pengo) = 0;

        virtual std::unique_ptr<PengoState>  OnMove(PengoComponent* pengo) = 0;
        virtual std::unique_ptr<PengoState>  OnPush(PengoComponent* pengo) = 0;
    
    };

    class PengoWalkingState : public PengoState
    {
        glm::vec3 m_TargetPosition{ FLT_MAX,FLT_MAX,FLT_MAX };
    public:
        void Enter(PengoComponent* pengo) override;
        std::unique_ptr<PengoState> Update(PengoComponent* pengo, float deltaTime) override;
        void Animate(PengoComponent* pengo, float deltaTime) override;
        void Exit(PengoComponent* pengo) override;

        std::unique_ptr<PengoState> OnMove(PengoComponent* pengo) override;
        std::unique_ptr<PengoState> OnPush(PengoComponent* pengo) override;
    };

    class PengoPushingState : public PengoState
    {
    public:
        PengoPushingState(int pushFrames) : m_PushFrames(pushFrames) {};

        void Enter(PengoComponent* pengo) override;
        std::unique_ptr<PengoState> Update(PengoComponent* pengo, float deltaTime) override;
        void Animate(PengoComponent* pengo, float deltaTime) override;
        void Exit(PengoComponent* pengo) override;

        std::unique_ptr<PengoState> OnMove(PengoComponent* pengo) override;
        std::unique_ptr<PengoState> OnPush(PengoComponent* pengo) override;

    private:
        int m_PushFrames;
    };

    class PengoDyingState : public PengoState
    {
    public:
        void Enter(PengoComponent* pengo) override;
        std::unique_ptr<PengoState> Update(PengoComponent* pengo, float deltaTime) override;
        void Animate(PengoComponent* pengo, float deltaTime) override;
        void Exit(PengoComponent* pengo) override;

        std::unique_ptr<PengoState> OnMove(PengoComponent* pengo) override;
        std::unique_ptr<PengoState> OnPush(PengoComponent* pengo) override;
    };
}