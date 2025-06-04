#include "EnemyControllerComponent.h"
#include <memory>
#include "TextureComponent.h"
#include "EnemyComponent.h"
#include "CppBehaviour.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "GridComponent.h"
#include "PengoComponent.h"
#include <iostream>

namespace dae
{
	void EnemyControllerComponent::Notify(const Event& event, GameObject* )
	{
		if (event.id == make_sdbm_hash("TileMoved"))
		{
			std::cout << "tile moved\n";
		}
	}
	
	void EnemyControllerComponent::Start()
	{
		m_GridLayoutPtr = m_GridPtr->GetGridLayout();
		for (int& idx : m_SnobeeTargetPosIdx)
		{
			idx = rand() % 195;
		}
		std::cout << "called this\n";
	}

	glm::vec3 getClosestCardinalDirection(const glm::vec3& direction) {
		float x = direction.x;
		float y = direction.y;

		if (std::abs(x) > std::abs(y)) {
			return glm::vec3((x > 0) ? 1.0f : -1.0f, 0.0f, 0.0f);
		}
		else {
			return glm::vec3(0.0f, (y > 0) ? 1.0f : -1.0f,0.f);
		}
	}

	void EnemyControllerComponent::Update(float deltaTime)
	{
		m_TotalDT += deltaTime;
		if (m_TotalDT > m_AttackInterval)
		{
			m_TotalDT -= m_AttackInterval;
			if (m_AttackingSnobees == 0)
			{
				m_AttackingSnobees = m_NextAttackingSnobees;
				++m_NextAttackingSnobees;
				if (m_NextAttackingSnobees > 3)
				{
					m_NextAttackingSnobees = rand() % 3 + 1;
				}
				m_AttackInterval = 5.f;
			}
			else
			{
				m_AttackingSnobees = 0;
				m_AttackInterval = 10.f;
			}

			for (int& idx : m_SnobeeTargetPosIdx)
			{
				idx = rand() % 195;
			}
		}

		while (m_SnobeesAlive < MAXIMUM_SNOBEES && m_SnobeesDead < 4)
		{
			int idx = std::distance(m_GridLayoutPtr->begin(), std::find_if(m_GridLayoutPtr->begin(), m_GridLayoutPtr->end(), [](const Tile& tile) {return tile == Tile::Sno_Bee; }));
			glm::vec3 pos = m_GridPtr->IdxToPoint(idx);
			m_GridPtr->RequestBreak(pos, {});
			SpawnEnemy(pos);
			++m_SnobeesAlive;
		}


		for (int idx{}; idx < static_cast<int>(m_Snobees.size()); ++idx)
		{
			if (m_PlayerControlled && idx == m_ControlledSnobee)
				continue;

			glm::vec3 snobeePos = m_Snobees[idx]->GetOwner()->GetWorldPosition();
			int currentIdx = m_GridPtr->PointToIdx(snobeePos);

			glm::vec3 targetPos{};

			if (idx >= m_AttackingSnobees)
			{
				while (currentIdx == m_SnobeeTargetPosIdx[idx] || m_GridLayoutPtr->at(m_SnobeeTargetPosIdx[idx]) == Tile::Unbreakable || m_GridLayoutPtr->at(m_SnobeeTargetPosIdx[idx]) == Tile::Sno_Bee)
					m_SnobeeTargetPosIdx[idx] = rand() % 195;

				targetPos = m_GridPtr->IdxToPoint(m_SnobeeTargetPosIdx[idx]);
			}
			else
			{
				targetPos = m_PengosPtr[0]->GetOwner()->GetWorldPosition();
			}

			glm::vec3 direction = targetPos - snobeePos;

			glm::vec3 finalDirection;
			if (glm::dot(direction, direction) > 1)
				finalDirection = getClosestCardinalDirection(direction);
			else
				finalDirection = {};

			int nextIdx = m_GridPtr->PointToIdx(snobeePos + glm::vec3{ finalDirection.x * TILE_WIDTH, finalDirection.y * TILE_WIDTH,0.f });
			
			if (m_GridLayoutPtr->at(nextIdx) == Tile::Unbreakable || m_GridLayoutPtr->at(nextIdx) == Tile::Sno_Bee)
			{
				finalDirection = { -finalDirection.y,finalDirection.x,0.f };
			}

			m_Snobees[idx]->Move(finalDirection);
			m_Snobees[idx]->Break();
		}
	}

	void EnemyControllerComponent::SpawnEnemy(const glm::vec2& position)
	{
		auto& scene = dae::SceneManager::GetInstance().GetScene();

		auto go = std::make_shared<dae::GameObject>();
		auto textureMovable = go->AddComponent<dae::TextureComponent>();
		textureMovable->SetTexture("Pengo_snobee_noBG.png");
		textureMovable->SetSourceRect(0, 160, 16, 16);
		textureMovable->SetWidthAndHeight(static_cast<float>(TILE_WIDTH), static_cast<float>(TILE_WIDTH));
		auto enemyC = go->AddComponent<dae::EnemyComponent>(200.f, m_GridPtr);
		m_Snobees.emplace_back(enemyC);
		go->SetLocalPosition(position.x,position.y);
		/*input.AddBinding<dae::MoveCommand<dae::EnemyComponent>>(XINPUT_GAMEPAD_DPAD_UP, dae::InputType::Controller, 1, go2.get(), glm::vec3{ 0,-1,0 }, pengoC2);
		input.AddBinding<dae::MoveCommand<dae::EnemyComponent>>(XINPUT_GAMEPAD_DPAD_DOWN, dae::InputType::Controller, 1, go2.get(), glm::vec3{ 0,1,0 }, pengoC2);
		input.AddBinding<dae::MoveCommand<dae::EnemyComponent>>(XINPUT_GAMEPAD_DPAD_LEFT, dae::InputType::Controller, 1, go2.get(), glm::vec3{ -1,0,0 }, pengoC2);
		input.AddBinding<dae::MoveCommand<dae::EnemyComponent>>(XINPUT_GAMEPAD_DPAD_RIGHT, dae::InputType::Controller, 1, go2.get(), glm::vec3{ 1,0,0 }, pengoC2);
		input.AddBinding<dae::BreakCommand>(XINPUT_GAMEPAD_A, dae::InputType::Controller, 1, go2.get(), pengoC2);*/
		//go->AddObserver(observer2);
		//go->AddObserver(observerAch);
		scene.Add(go);
	}

	void EnemyControllerComponent::AddPengo(PengoComponent* pengo)
	{
		m_PengosPtr.emplace_back(pengo);
	}

	void EnemyControllerComponent::Move(const glm::vec3 direction)
	{
		m_Snobees[m_ControlledSnobee]->Move(direction);
	}

	void EnemyControllerComponent::Break()
	{
		m_Snobees[m_ControlledSnobee]->Break();
	}

	void EnemyControllerComponent::PlayerControlled(bool playerControlled)
	{
		m_PlayerControlled = playerControlled;
	}

	EnemyControllerComponent::EnemyControllerComponent(GridComponent* grid): 
		m_GridPtr{grid}
	{

	}
}