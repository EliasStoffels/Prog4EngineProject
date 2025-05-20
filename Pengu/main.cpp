#include <SDL.h>
//#include <steam_api.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "FpsComponent.h"
#include <iostream>
#include "RotateComponent.h"
#include "InputManager.h"
#include "MoveCommand.h"
#include "HealthComponent.h"
#include "DieCommand.h"
#include "UiObserver.h"
#include "KillEnemyCommand.h"
#include <SteamAchievements.h>
#include <AchievementObserver.h>
#include "ServiceLocator.h"
#include "mixerSoundSystem.h"
#include "LoggingSoundSystem.h"
#include "GridComponent.h"
#include "PengoComponent.h"
#include "PushCommand.h"
#include "WallComponent.h"

void load()
{
	const int GRID_WIDTH{ 13 };
	const int GRID_HEIGHT{ 15 };
	const int TILE_WIDTH{ 48 };
	const glm::vec2 GRID_OFSETT{ 24,106 };

	auto& input = dae::InputManager::GetInstance();
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Pengo");

	//fonts
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	//auto smallFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 14);

	//background
	auto go = std::make_shared<dae::GameObject>();
	dae::TextureComponent* textureC1 = go->AddComponent<dae::TextureComponent>();
	textureC1->SetTexture("BlackBG.png");
	textureC1->SetWidthAndHeight(672, 768);
	go->SetLocalPosition(0, 82);
	scene.Add(go);

	//walls
	go = std::make_shared<dae::GameObject>();
	auto vertWallTex = go->AddComponent<dae::TextureComponent>();
	vertWallTex->SetTexture("VerticalWallTex.png");
	vertWallTex->IsActive(false);
	auto horWallTex = go->AddComponent<dae::TextureComponent>();
	horWallTex->SetTexture("HorizontalWallTex.png");
	horWallTex->IsActive(false);
	auto wallComp = go->AddComponent<dae::WallComponent>(GRID_OFSETT, glm::vec2{ GRID_WIDTH * TILE_WIDTH, GRID_HEIGHT * TILE_WIDTH }, vertWallTex, horWallTex);
	scene.Add(go);

	//grid
	go = std::make_shared<dae::GameObject>();
	auto gridC = go->AddComponent<dae::GridComponent>(GRID_WIDTH,GRID_HEIGHT,TILE_WIDTH,GRID_OFSETT, wallComp);
	//gridC->SaveLevel();
	gridC->LoadLevel(4);
	scene.Add(go);

	//text
	go = std::make_shared<dae::GameObject>();
	auto text = go->AddComponent<dae::TextComponent>(font);
	text->SetText("controls: WASD and E or D-PAD and South button");
	scene.Add(go);

	//UiGo
	//auto observerGo = std::make_shared<dae::GameObject>();
	//observerGo->SetLocalPosition(10, 120);
	//auto observer = observerGo->AddComponent<dae::UiObserverComponent>(
	//	observerGo->AddComponent<dae::TextComponent>(smallFont),
	//	observerGo->AddComponent<dae::TextComponent>(smallFont, "", glm::vec3{ 0.f,20.f,0.f }));
	//scene.Add(observerGo);
	//
	//observerGo = std::make_shared<dae::GameObject>();
	//observerGo->SetLocalPosition(10, 160);
	//auto observer2 = observerGo->AddComponent<dae::UiObserverComponent>(
	//	observerGo->AddComponent<dae::TextComponent>(smallFont),
	//	observerGo->AddComponent<dae::TextComponent>(smallFont, "", glm::vec3{ 0.f,20.f,0.f }));
	//scene.Add(observerGo);
	//
	//observerGo = std::make_shared<dae::GameObject>();
	//auto observerAch = observerGo->AddComponent<dae::AchievementComponent>();
	//scene.Add(observerGo);

	//movable
	//go = std::make_shared<dae::GameObject>();
	//dae::TextureComponent* textureMovable = go->AddComponent<dae::TextureComponent>();
	//textureMovable->SetTexture("Pengo_snobee.png");
	//textureMovable->SetSourceRect(0, 0, 16, 16);
	//textureMovable->SetWidthAndHeight(45, 45);
	//go->AddComponent<dae::HealthComponent>(100.f, 3);
	//go->AddComponent<dae::ScoreComponent>();
	//auto pengoC = go->AddComponent<dae::PengoComponent>(200.f, gridC);
	//go->SetLocalPosition((GRID_OFSETT.x + (GRID_WIDTH / 2) * TILE_WIDTH), (GRID_OFSETT.y + ((GRID_HEIGHT / 2) - 1) * TILE_WIDTH));
	//input.AddBinding<dae::MoveCommand>(XINPUT_GAMEPAD_DPAD_UP, dae::InputType::Controller, go.get(), glm::vec2{0,-1},gridC, pengoC);
	//input.AddBinding<dae::MoveCommand>(XINPUT_GAMEPAD_DPAD_DOWN, dae::InputType::Controller, go.get(), glm::vec2{ 0,1 }, gridC, pengoC);
	//input.AddBinding<dae::MoveCommand>(XINPUT_GAMEPAD_DPAD_LEFT, dae::InputType::Controller, go.get(), glm::vec2{ -1,0 }, gridC, pengoC);
	//input.AddBinding<dae::MoveCommand>(XINPUT_GAMEPAD_DPAD_RIGHT, dae::InputType::Controller, go.get(), glm::vec2{1,0}, gridC, pengoC);
	////input.AddBinding<dae::DieCommand>(XINPUT_GAMEPAD_A, dae::InputType::Controller, go.get());
	//input.AddBinding<dae::PushCommand>(XINPUT_GAMEPAD_A, dae::InputType::Controller, go.get(), pengoC);
	////go->AddObserver(observer2);
	////go->AddObserver(observerAch);
	//scene.Add(go);
	
	go = std::make_shared<dae::GameObject>();
	dae::TextureComponent* textureMovable = go->AddComponent<dae::TextureComponent>();
	textureMovable->SetTexture("Pengo_snobee.png");
	textureMovable->SetSourceRect(0, 0, 16, 16);
	textureMovable->SetWidthAndHeight(TILE_WIDTH, TILE_WIDTH);
	go->AddComponent<dae::HealthComponent>(100.f, 3);
	go->AddComponent<dae::ScoreComponent>();
	auto pengoC = go->AddComponent<dae::PengoComponent>(200.f, gridC);
	go->SetLocalPosition((GRID_OFSETT.x + (GRID_WIDTH / 2) * TILE_WIDTH), (GRID_OFSETT.y + ((GRID_HEIGHT / 2) - 1) * TILE_WIDTH));
	input.AddBinding<dae::MoveCommand>(SDL_SCANCODE_W, dae::InputType::Keyboard, -1, go.get(), glm::vec3{ 0,-1,0 }, pengoC);
	input.AddBinding<dae::MoveCommand>(SDL_SCANCODE_S, dae::InputType::Keyboard, -1, go.get(), glm::vec3{ 0,1,0 }, pengoC);
	input.AddBinding<dae::MoveCommand>(SDL_SCANCODE_A, dae::InputType::Keyboard, -1, go.get(), glm::vec3{ -1,0,0 }, pengoC);
	input.AddBinding<dae::MoveCommand>(SDL_SCANCODE_D, dae::InputType::Keyboard, -1, go.get(), glm::vec3{ 1,0,0 }, pengoC);
	input.AddBinding<dae::MoveCommand>(XINPUT_GAMEPAD_DPAD_UP, dae::InputType::Controller, 0, go.get(), glm::vec3{ 0,-1,0 }, pengoC);
	input.AddBinding<dae::MoveCommand>(XINPUT_GAMEPAD_DPAD_DOWN, dae::InputType::Controller, 0, go.get(), glm::vec3{ 0,1,0 }, pengoC);
	input.AddBinding<dae::MoveCommand>(XINPUT_GAMEPAD_DPAD_LEFT, dae::InputType::Controller, 0, go.get(), glm::vec3{ -1,0,0 }, pengoC);
	input.AddBinding<dae::MoveCommand>(XINPUT_GAMEPAD_DPAD_RIGHT, dae::InputType::Controller, 0, go.get(), glm::vec3{ 1,0,0 }, pengoC);
	//input.AddBinding<dae::DieCommand>(SDL_SCANCODE_Q, dae::InputType::Keyboard, go.get());
	input.AddBinding<dae::PushCommand>(SDL_SCANCODE_E, dae::InputType::Keyboard, 0, go.get(), pengoC);
	input.AddBinding<dae::PushCommand>(XINPUT_GAMEPAD_A, dae::InputType::Controller, 0, go.get(), pengoC);
	//go->AddObserver(observer2);
	//go->AddObserver(observerAch);
	scene.Add(go);

	auto go2 = std::make_shared<dae::GameObject>();
	auto textureMovable2 = go2->AddComponent<dae::TextureComponent>();
	textureMovable2->SetTexture("Pengo_snobee.png");
	textureMovable2->SetSourceRect(0, 0, 16, 16);
	textureMovable2->SetWidthAndHeight(TILE_WIDTH, TILE_WIDTH);
	go2->AddComponent<dae::HealthComponent>(100.f, 3);
	go2->AddComponent<dae::ScoreComponent>();
	auto pengoC2 = go2->AddComponent<dae::PengoComponent>(200.f, gridC);
	go2->SetLocalPosition((GRID_OFSETT.x + (GRID_WIDTH / 2) * TILE_WIDTH), (GRID_OFSETT.y + ((GRID_HEIGHT / 2) - 1) * TILE_WIDTH));
	input.AddBinding<dae::MoveCommand>(SDL_SCANCODE_W, dae::InputType::Keyboard, -1, go2.get(), glm::vec3{ 0,-1,0 }, pengoC2);
	input.AddBinding<dae::MoveCommand>(SDL_SCANCODE_S, dae::InputType::Keyboard, -1, go2.get(), glm::vec3{ 0,1,0 }, pengoC2);
	input.AddBinding<dae::MoveCommand>(SDL_SCANCODE_A, dae::InputType::Keyboard, -1, go2.get(), glm::vec3{ -1,0,0 }, pengoC2);
	input.AddBinding<dae::MoveCommand>(SDL_SCANCODE_D, dae::InputType::Keyboard, -1, go2.get(), glm::vec3{ 1,0,0 }, pengoC2);
	input.AddBinding<dae::MoveCommand>(XINPUT_GAMEPAD_DPAD_UP, dae::InputType::Controller, 1, go2.get(), glm::vec3{ 0,-1,0 }, pengoC2);
	input.AddBinding<dae::MoveCommand>(XINPUT_GAMEPAD_DPAD_DOWN, dae::InputType::Controller, 1, go2.get(), glm::vec3{ 0,1,0 }, pengoC2);
	input.AddBinding<dae::MoveCommand>(XINPUT_GAMEPAD_DPAD_LEFT, dae::InputType::Controller, 1, go2.get(), glm::vec3{ -1,0,0 }, pengoC2);
	input.AddBinding<dae::MoveCommand>(XINPUT_GAMEPAD_DPAD_RIGHT, dae::InputType::Controller, 1, go2.get(), glm::vec3{ 1,0,0 }, pengoC2);
	//input.AddBinding<dae::DieCommand>(SDL_SCANCODE_Q, dae::InputType::Keyboard, go.get());
	input.AddBinding<dae::PushCommand>(SDL_SCANCODE_E, dae::InputType::Keyboard, 1, go2.get(), pengoC2);
	input.AddBinding<dae::PushCommand>(XINPUT_GAMEPAD_A, dae::InputType::Controller, 1, go2.get(), pengoC2);
	//go->AddObserver(observer2);
	//go->AddObserver(observerAch);
	scene.Add(go2);
}

int main(int, char* []) {
	dae::ServiceLocator::GetInstance().RegisterSoundSystem(std::make_unique<dae::MixerSoundSystem>());

	dae::ServiceLocator::GetInstance().GetSoundSystem().LoadMusic(static_cast<dae::sound_id>(dae::make_sdbm_hash("BGMusic")), "../Data/PengoSoundFX/Main_BGM_Popcorn.mp3");
	dae::ServiceLocator::GetInstance().GetSoundSystem().PlayLooping(static_cast<dae::sound_id>(dae::make_sdbm_hash("BGMusic")), 100.f,-1);

	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}