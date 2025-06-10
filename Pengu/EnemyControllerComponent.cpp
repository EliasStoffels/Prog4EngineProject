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
#include "EventArgs.h"
#include <algorithm>
#include <iostream>
#include "GameStateManager.h"

namespace dae
{
	void EnemyControllerComponent::Notify(const Event& event, GameObject* gameObject)
	{
		if (event.id == make_sdbm_hash("TileMoved"))
		{
			TileMoveArg* args = reinterpret_cast<TileMoveArg*>(event.arg);
			int tileWidth{ 48 };
			int leeWay{ 4 };
			tileWidth -= leeWay;

			std::vector<EnemyComponent*> snobeesToRemove;

			for (auto snobee : m_Snobees)
			{
				glm::vec3 snobeePos = snobee->GetOwner()->GetWorldPosition() + glm::vec3{ leeWay/2,leeWay/2,0 };
				glm::vec3 nextTilePos = args->position + args->direction + glm::vec3{ leeWay/2,leeWay/2,0 };
				glm::vec3 currentTilePos = args->position;

				/*bool isOnCurrentTile =
					(snobeePos.x < currentTilePos.x + tileWidth &&
					snobeePos.x + tileWidth > currentTilePos.x &&
					snobeePos.y < currentTilePos.y + tileWidth &&
					snobeePos.y + tileWidth > currentTilePos.y);*/

				bool isOnNextTile =
					(snobeePos.x < nextTilePos.x + tileWidth &&
					snobeePos.x + tileWidth > nextTilePos.x &&
					snobeePos.y < nextTilePos.y + tileWidth &&
					snobeePos.y + tileWidth > nextTilePos.y);

				if (/*isOnCurrentTile || */isOnNextTile)
				{
					snobee->GetHit(gameObject);
					snobee->GetOwner()->SetLocalPosition(args->direction * static_cast<float>(tileWidth));
					snobeesToRemove.push_back(snobee);
				}
			}

			m_Snobees.erase(
				std::remove_if(
					m_Snobees.begin(),
					m_Snobees.end(),
					[&snobeesToRemove](EnemyComponent* snobee) {
						return std::find(snobeesToRemove.begin(), snobeesToRemove.end(), snobee) != snobeesToRemove.end();
					}),
				m_Snobees.end()
			);
			
		}
		else if (event.id == make_sdbm_hash("EnemyDied"))
		{
			++m_SnobeesDead;
			if(gameObject->GetParent()) // if it has a parent that means it died from a block being pushed onto it
				--m_SnobeesAlive;
			else
				GetOwner()->NotifyObservers(Event{ make_sdbm_hash("SnobeeHatched"), nullptr });

			if (m_SnobeesDead == 6)
			{
				GetOwner()->NotifyObservers(Event{ make_sdbm_hash("LevelWon"), nullptr });
			}
		}
		else if (event.id == make_sdbm_hash("Respawn"))
		{
			ResetEnemyPos();
			m_Freeze = false;
		}
	}
	
	void EnemyControllerComponent::Start()
	{
		m_GridLayoutPtr = m_GridPtr->GetGridLayout();
		for (int& idx : m_SnobeeTargetPosIdx)
		{
			idx = rand() % 195;
		}
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
		if (m_Freeze || GameStateManager::GetInstance().playersDead)
			return;

		// attack / explore mode
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
				m_AttackInterval = 2.f;
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

		//score
		if(m_PrevSnobeesDead != m_SnobeesDead)
		{
			ScoreChangedArgs args{ 500 * (m_SnobeesDead - m_PrevSnobeesDead) };
			GetOwner()->NotifyObservers(Event{ make_sdbm_hash("ScoreChanged"), &args });
			m_PrevSnobeesDead = m_SnobeesDead;
		}

		//spawning
		while (m_SnobeesAlive < MAXIMUM_SNOBEES && m_SnobeesDead < 4)
		{
			std::cout << "spawned enemy\n";
			int idx = std::distance(m_GridLayoutPtr->begin(), std::find_if(m_GridLayoutPtr->begin(), m_GridLayoutPtr->end(), [](const Tile& tile) {return tile == Tile::Sno_Bee; }));
			glm::vec3 pos = m_GridPtr->IdxToPoint(idx);
			m_GridPtr->RequestBreak(pos, {});
			++m_SnobeesAlive;
			SpawnEnemy(pos);
		}

		// movement 
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
				targetPos = m_PengosPtr[idx%m_PengosPtr.size()]->GetOwner()->GetWorldPosition();
			}

			glm::vec3 direction = targetPos - snobeePos;

			glm::vec3 finalDirection;
			if (glm::dot(direction, direction) > 1)
				finalDirection = getClosestCardinalDirection(direction);
			else
				finalDirection = {};

			int nextIdx = m_GridPtr->PointToIdx(snobeePos + glm::vec3{ finalDirection.x * TILE_WIDTH, finalDirection.y * TILE_WIDTH,0.f });
			
			nextIdx = std::clamp(nextIdx, 0, 194);
			if (m_GridLayoutPtr->at(nextIdx) == Tile::Unbreakable || m_GridLayoutPtr->at(nextIdx) == Tile::Sno_Bee)
			{
				finalDirection = { -finalDirection.y,finalDirection.x,0.f };
			}

			m_Snobees[idx]->Move(finalDirection);
			m_Snobees[idx]->Break();
		}

		int tileWidth{ 48 };
		int leeWay{ 4 };
		tileWidth -= leeWay;

		// pengo hitchecks
		for (auto pengo : m_PengosPtr)
		{
			auto pengoPos = pengo->GetOwner()->GetWorldPosition() + glm::vec3{ leeWay / 2,leeWay / 2,0 };

			for (auto snobee : m_Snobees)
			{
				auto snobeePos = snobee->GetOwner()->GetWorldPosition() + glm::vec3{ leeWay / 2,leeWay / 2,0 };

				if (pengoPos.x < snobeePos.x + tileWidth &&
					pengoPos.x + tileWidth > snobeePos.x &&
					pengoPos.y < snobeePos.y + tileWidth &&
					pengoPos.y + tileWidth > snobeePos.y)
				{
					pengo->Die();
					++m_PengosDead;
					if (m_PengosDead == static_cast<int>(m_PengosPtr.size()))
					{
						GetOwner()->NotifyObservers(Event{ make_sdbm_hash("PengoDied"), nullptr });
						m_Freeze = true;
					}
					break; 
				}
			}
		}
	}

	void EnemyControllerComponent::SpawnEnemy(const glm::vec2& position)
	{
		auto& scene = dae::SceneManager::GetInstance().GetScene();

		auto go = scene.AddEmpty();
		auto textureMovable = go->AddComponent<dae::TextureComponent>();
		textureMovable->SetTexture("Pengo_snobee_noBG.png");
		textureMovable->SetSourceRect(0, 160, 16, 16);
		textureMovable->SetWidthAndHeight(static_cast<float>(TILE_WIDTH), static_cast<float>(TILE_WIDTH));
		auto enemyC = go->AddComponent<dae::EnemyComponent>(150.f, m_GridPtr);
		m_Snobees.emplace_back(enemyC);
		go->SetLocalPosition(position.x,position.y, 10);
		go->AddObserver(this);

		GetOwner()->NotifyObservers(Event{ make_sdbm_hash("SnobeeHatched"), nullptr });

	}

	void EnemyControllerComponent::ResetEnemyPos()
	{
		for (int idx{}; idx < static_cast<int>(m_Snobees.size()); ++idx)
		{
			switch (idx % static_cast<int>(m_Snobees.size()))
			{
			case 0:
			{
				m_Snobees[idx]->Reset(0);
			}
			break;
			case 1:
			{
				m_Snobees[idx]->Reset(12);
			}
			break;
			case 2:
			{
				m_Snobees[idx]->Reset(182);
			}
			break;
			}
		}
		m_PengosDead = 0;
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

	EnemyControllerComponent::EnemyControllerComponent(GameObject* owner,GridComponent* grid): 
		CppBehaviour{owner}, m_GridPtr{grid}
	{

	}
}