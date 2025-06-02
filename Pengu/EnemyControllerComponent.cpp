#include "EnemyControllerComponent.h"
#include <memory>
#include "TextureComponent.h"
#include "EnemyComponent.h"
#include "CppBehaviour.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "GridComponent.h"

namespace dae
{
	void EnemyControllerComponent::Start()
	{
		m_GridLayout = m_GridPtr->GetGridLayout();
	}

	void EnemyControllerComponent::Update(float )
	{
		while (m_SnobeesAlive < MAXIMUM_SNOBEES)
		{
			int idx = std::distance(m_GridLayout->begin(), std::find_if(m_GridLayout->begin(), m_GridLayout->end(), [](const Tile& tile) {return tile == Tile::Sno_Bee; }));
			glm::vec3 pos = m_GridPtr->IdxToPoint(idx);
			m_GridPtr->RequestBreak(pos, {});
			SpawnEnemy(pos);
			++m_SnobeesAlive;
		}
	}

	void EnemyControllerComponent::SpawnEnemy(const glm::vec2& position)
	{
		auto& scene = dae::SceneManager::GetInstance().GetScene("Pengo");

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

	EnemyControllerComponent::EnemyControllerComponent(GridComponent* grid): 
		m_GridPtr{grid}
	{

	}
}