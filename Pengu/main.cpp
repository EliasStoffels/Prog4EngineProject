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

void load()
{
	auto& input = dae::InputManager::GetInstance();
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	//create gameObject
	auto go = std::make_shared<dae::GameObject>();
	auto fpsGo = std::make_shared<dae::GameObject>();

	//fonts
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto smallFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 14);

	//textures
	dae::TextureComponent* textureC1 = go->AddComponent<dae::TextureComponent>();
	textureC1->SetTexture("background.tga");
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	dae::TextureComponent* textureC2 = go->AddComponent<dae::TextureComponent>();
	textureC2->SetTexture("logo.tga");
	go->SetLocalPosition(216, 180);
	scene.Add(go);

	//// root Game Object;
	//auto rootGo = std::make_shared<dae::GameObject>();
	//rootGo->SetLocalPosition(500, 300);
	//scene.Add(rootGo);

	//// parent game object
	//auto parentGo = std::make_shared<dae::GameObject>();
	//dae::TextureComponent* textureTemp = parentGo->AddComponent<dae::TextureComponent>();
	//textureTemp->SetTexture("pengo.tga");
	////dae::RotateComponent* parentRotatec = parentGo->AddComponent<dae::RotateComponent>();
	////parentRotatec->SetRadius(30.f);
	////parentRotatec->SetRadianPerSecond(static_cast<float>(M_PI));
	//parentGo->SetLocalPosition(200, 200);
	//parentGo->SetParent(rootGo.get(), false);
	//scene.Add(parentGo);

	//// child game object
	//go = std::make_shared<dae::GameObject>();
	//dae::TextureComponent* textureC3 = go->AddComponent<dae::TextureComponent>();
	//textureC3->SetTexture("pengo.tga");
	//dae::RotateComponent* rotatec = go->AddComponent<dae::RotateComponent>();
	//rotatec->SetRadius(30.f);
	//rotatec->SetRadianPerSecond(static_cast<float>(-M_PI/2));
	//go->SetLocalPosition(30, 30);
	//go->SetParent(parentGo.get(), false);
	//scene.Add(go);

	//text
	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::TextComponent>(font, "Programming 4 Assignement");
	go->SetLocalPosition(80, 30);
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::TextComponent>(smallFont, "use WASD for first character movement, Q to die, E to kill enemy");
	go->AddComponent<dae::TextComponent>(smallFont, "use DPAD for second character movement, A to die, X to kill enemy", glm::vec3{ 0,20,0 });
	go->SetLocalPosition(10, 80);
	scene.Add(go);


	//fps
	fpsGo->AddComponent<dae::FpsComponent>();
	fpsGo->AddComponent<dae::TextComponent>(font, "number");
	scene.Add(fpsGo);

	//UiGo
	auto observerGo = std::make_shared<dae::GameObject>();
	observerGo->SetLocalPosition(10, 120);
	auto observer = observerGo->AddComponent<dae::UiObserverComponent>(
		observerGo->AddComponent<dae::TextComponent>(smallFont),
		observerGo->AddComponent<dae::TextComponent>(smallFont, "", glm::vec3{ 0.f,20.f,0.f }));
	scene.Add(observerGo);

	observerGo = std::make_shared<dae::GameObject>();
	observerGo->SetLocalPosition(10, 160);
	auto observer2 = observerGo->AddComponent<dae::UiObserverComponent>(
		observerGo->AddComponent<dae::TextComponent>(smallFont),
		observerGo->AddComponent<dae::TextComponent>(smallFont, "", glm::vec3{ 0.f,20.f,0.f }));
	scene.Add(observerGo);

	observerGo = std::make_shared<dae::GameObject>();
	auto observerAch = observerGo->AddComponent<dae::AchievementComponent>();
	scene.Add(observerGo);

	//movable
	go = std::make_shared<dae::GameObject>();
	dae::TextureComponent* textureMovable = go->AddComponent<dae::TextureComponent>();
	textureMovable->SetTexture("pengo.tga");
	go->AddComponent<dae::HealthComponent>(100.f, 3);
	go->AddComponent<dae::ScoreComponent>();
	go->SetLocalPosition(300, 300);
	input.AddBinding<dae::MoveCommand>(XINPUT_GAMEPAD_DPAD_UP, dae::InputType::Controller, go.get(), 200.f, dae::Direction::Up);
	input.AddBinding<dae::MoveCommand>(XINPUT_GAMEPAD_DPAD_DOWN, dae::InputType::Controller, go.get(), 200.f, dae::Direction::Down);
	input.AddBinding<dae::MoveCommand>(XINPUT_GAMEPAD_DPAD_LEFT, dae::InputType::Controller, go.get(), 200.f, dae::Direction::Left);
	input.AddBinding<dae::MoveCommand>(XINPUT_GAMEPAD_DPAD_RIGHT, dae::InputType::Controller, go.get(), 200.f, dae::Direction::Right);
	input.AddBinding<dae::DieCommand>(XINPUT_GAMEPAD_A, dae::InputType::Controller, go.get());
	input.AddBinding<dae::KillEnemyCommand>(XINPUT_GAMEPAD_X, dae::InputType::Controller, go.get());
	go->AddObserver(observer2);
	go->AddObserver(observerAch);
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	dae::TextureComponent* textureMovable2 = go->AddComponent<dae::TextureComponent>();
	textureMovable2->SetTexture("pengo.tga");
	go->AddComponent<dae::HealthComponent>(100.f, 3);
	go->AddComponent<dae::ScoreComponent>();
	go->SetLocalPosition(200, 300);
	input.AddBinding<dae::MoveCommand>(SDL_SCANCODE_W, dae::InputType::Keyboard, go.get(), 100.f, dae::Direction::Up);
	input.AddBinding<dae::MoveCommand>(SDL_SCANCODE_S, dae::InputType::Keyboard, go.get(), 100.f, dae::Direction::Down);
	input.AddBinding<dae::MoveCommand>(SDL_SCANCODE_A, dae::InputType::Keyboard, go.get(), 100.f, dae::Direction::Left);
	input.AddBinding<dae::MoveCommand>(SDL_SCANCODE_D, dae::InputType::Keyboard, go.get(), 100.f, dae::Direction::Right);
	input.AddBinding<dae::DieCommand>(SDL_SCANCODE_Q, dae::InputType::Keyboard, go.get());
	input.AddBinding<dae::KillEnemyCommand>(SDL_SCANCODE_E, dae::InputType::Keyboard, go.get());
	go->AddObserver(observer);
	go->AddObserver(observerAch);
	scene.Add(go);
}

int main(int, char* []) {

	
	//serviceLocator.RegisterSoundSystem(std::make_unique<dae::LoggingSoundSystem>(std::make_unique<dae::MixerSoundSystem>()));

	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}