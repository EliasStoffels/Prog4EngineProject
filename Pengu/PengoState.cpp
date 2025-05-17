// PengoState.cpp
#include "PengoState.h"
#include "PengoComponent.h"
#include "TextureComponent.h"
#include "GridComponent.h"
#include <iostream>

namespace dae
{
    // Walking State
    //============================================================================================================================================================================================
    void PengoWalkingState::Enter(PengoComponent* pengo)
    {
        m_TexturePtr = pengo->GetTexture();
        m_TexturePtr->SetSourceRect(0, 0);
    }

    std::unique_ptr<PengoState>  PengoWalkingState::Update(PengoComponent* pengo, float deltaTime)
    {
        auto transform = pengo->GetOwner()->GetTransform();
        glm::vec3 direction = (m_TargetPosition - transform->GetWorldPosition());

        float sqrLength = glm::dot(direction, direction);
        if (sqrLength < 4)
        {
            transform->SetLocalPosition(m_TargetPosition - transform->GetWorldPosition() + transform->GetLocalPosition());
        }
        else
        {
            float length = std::sqrt(sqrLength);
            direction.x /= length;
            direction.y /= length;

            direction.x *= (pengo->GetSpeed() * deltaTime);
            direction.y *= (pengo->GetSpeed() * deltaTime);

            if (m_TargetPosition.x != FLT_MAX)
                transform->Move(direction);
        }
        Animate(pengo, deltaTime);

        return nullptr;
    }

    void PengoWalkingState::Animate(PengoComponent* pengo, float deltaTime)
    {
        m_TotalDT += deltaTime;
        if (m_TotalDT > FRAME_DELAY)
        {
            m_TotalDT -= FRAME_DELAY;

            if (pengo->GetOwner()->GetWorldPosition() != m_TargetPosition && m_TargetPosition.x != FLT_MAX)
                ++m_CurrentFrame %= 2;
            else
                m_CurrentFrame = 0;

            int currentFrameOffset = 16 * m_CurrentFrame;

            if (m_Direction.x < 0)
            {
                m_TexturePtr->SetSourceRect(32 + currentFrameOffset, 0);
            }
            if (m_Direction.x > 0)
            {
                m_TexturePtr->SetSourceRect(96 + currentFrameOffset, 0);
            }
            if (m_Direction.y < 0)
            {
                m_TexturePtr->SetSourceRect(64 + currentFrameOffset, 0);
            }
            if (m_Direction.y > 0)
            {
                m_TexturePtr->SetSourceRect(currentFrameOffset, 0);
            }
        }
    }

    void PengoWalkingState::Exit(PengoComponent* pengo)
    {
        pengo->GetOwner()->SetLocalPosition(m_TargetPosition - pengo->GetOwner()->GetWorldPosition() + pengo->GetOwner()->GetLocalPosition());
    }

    std::unique_ptr<PengoState> PengoWalkingState::OnMove(PengoComponent* pengo)
    {
        if (m_TargetPosition == pengo->GetOwner()->GetWorldPosition() || m_TargetPosition.x == FLT_MAX)
        {
            m_Direction = pengo->GetDirection();
            auto goTransform = pengo->GetOwner()->GetTransform();
            auto currentPos = goTransform->GetWorldPosition();
            m_TargetPosition = pengo->GetGrid()->RequestMove(currentPos, m_Direction);
        }

        return nullptr;
    }

    std::unique_ptr<PengoState> PengoWalkingState::OnPush(PengoComponent* pengo)
    {
        if (m_TargetPosition != pengo->GetOwner()->GetWorldPosition() && m_TargetPosition.x != FLT_MAX)
            return nullptr;
            
        auto blockState = pengo->GetGrid()->RequestPush(pengo->GetOwner()->GetWorldPosition(), m_Direction);
        
        if (blockState == BlockState::Sliding)
        {
            return std::make_unique<PengoPushingState>(m_Direction, 2);
        }
        else if (blockState == BlockState::Breaking)
        {
            return std::make_unique<PengoPushingState>(m_Direction, 6);
        }

        return nullptr;
    }

    // Pushing State
    //============================================================================================================================================================================================
    void PengoPushingState::Enter(PengoComponent* pengo)
    {
        m_Direction = pengo->GetDirection();
        m_TexturePtr = pengo->GetTexture();
        m_CurrentFrame = 0;

        if (m_Direction.x < 0)
        {
            m_TexturePtr->SetSourceRect(32, 16);
        }
        if (m_Direction.x > 0)
        {
            m_TexturePtr->SetSourceRect(96, 16);
        }
        if (m_Direction.y < 0)
        {
            m_TexturePtr->SetSourceRect(64, 16);
        }
        if (m_Direction.y > 0)
        {
            m_TexturePtr->SetSourceRect(0, 16);
        }
    }

    std::unique_ptr<PengoState> PengoPushingState::Update(PengoComponent* pengo, float deltaTime)
    {
        Animate(pengo, deltaTime);
        if (m_CurrentFrame >= m_PushFrames)
        {
            return std::make_unique<PengoWalkingState>(m_Direction);
        }

        return nullptr;
    }

   void PengoPushingState::Animate(PengoComponent*, float deltaTime)
    {
       m_TotalDT += deltaTime;
       if (m_TotalDT > FRAME_DELAY)
       {
           m_TotalDT -= FRAME_DELAY;
           ++m_CurrentFrame;

           int currentFrameOffset = 16 * (m_CurrentFrame % 2);
           if (m_Direction.x < 0)
           {
               m_TexturePtr->SetSourceRect(32 + currentFrameOffset, 16);
           }
           if (m_Direction.x > 0)
           {
               m_TexturePtr->SetSourceRect(96 + currentFrameOffset, 16);
           }
           if (m_Direction.y < 0)
           {
               m_TexturePtr->SetSourceRect(64 + currentFrameOffset, 16);
           }
           if (m_Direction.y > 0)
           {
               m_TexturePtr->SetSourceRect(currentFrameOffset, 16);
           }
       }
    }

    void PengoPushingState::Exit(PengoComponent* )
    {
    }

    std::unique_ptr<PengoState>  PengoPushingState::OnMove(PengoComponent* )
    {
        return nullptr;
    }

    std::unique_ptr<PengoState>  PengoPushingState::OnPush(PengoComponent* )
    {
        return nullptr;
    }

    // Dying State
    //============================================================================================================================================================================================
    void PengoDyingState::Enter(PengoComponent* )
    {
        // Setup dying animation
    }

    std::unique_ptr<PengoState>  PengoDyingState::Update(PengoComponent* , float )
    {
        return nullptr;
    }

    void PengoDyingState::Animate(PengoComponent*, float )
    {
    }

    void PengoDyingState::Exit(PengoComponent* )
    {
    }

    std::unique_ptr<PengoState>  PengoDyingState::OnMove(PengoComponent* )
    {
        return nullptr;
    }

    std::unique_ptr<PengoState>  PengoDyingState::OnPush(PengoComponent* )
    {
        return nullptr;
    }
}