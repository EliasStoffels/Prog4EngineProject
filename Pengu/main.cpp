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
#include <iostream>
#include "InputManager.h"
#include "MoveCommand.h"
#include "UiObserver.h"
#include <SteamAchievements.h>
#include "ServiceLocator.h"
#include "mixerSoundSystem.h"
#include "LoggingSoundSystem.h"
#include "GridComponent.h"
#include "PengoComponent.h"
#include "PushCommand.h"
#include "WallComponent.h"
#include "EnemyComponent.h"
#include "BreakCommand.h"
#include "EnemyControllerComponent.h"
#include "StartCommand.h"

void LoadPengo()
{
	const int GRID_WIDTH{ 13 };
	const int GRID_HEIGHT{ 15 };
	const int TILE_WIDTH{ 48 };
	const glm::vec2 GRID_OFSETT{ 24,106 };

	auto& input = dae::InputManager::GetInstance();
	auto& scene = dae::SceneManager::GetInstance().GetScene("Pengo");

	//fonts
	auto font = dae::ResourceManager::GetInstance().LoadFont("Pengo-Atari 5200.ttf", 20);
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
	scene.Add(go);

	//static ui
	go = std::make_shared<dae::GameObject>();
	dae::TextureComponent* textureSaticUi = go->AddComponent<dae::TextureComponent>();
	textureSaticUi->SetTexture("StaticUi.png");
	textureSaticUi->SetWidthAndHeight(672, 20);
	scene.Add(go);
	
	// dynamic ui
	go = std::make_shared<dae::GameObject>();
	auto textScore = go->AddComponent<dae::TextComponent>(font);
	textScore->SetRenderOfSet(glm::vec3{ 220,2,0 });
	auto textureSnobeeEggs = go->AddComponent<dae::TextureComponent>();
	textureSnobeeEggs->SetTexture("Misc.png");
	textureSnobeeEggs->SetWidthAndHeight(18, 18);
	textureSnobeeEggs->SetSourceRect(80,82,8,8);
	textureSnobeeEggs->SetRepeats(6);
	textureSnobeeEggs->SetRepeatOfsett(glm::vec3{-20,0,0});
	textureSnobeeEggs->SetRenderOfsett(glm::vec3{ 400,60,0 });
	auto uiObserver = go->AddComponent<dae::UIObserverComponent>(textureSnobeeEggs,textScore);
	scene.Add(go);

	//pengo
	go = std::make_shared<dae::GameObject>();
	dae::TextureComponent* textureMovable = go->AddComponent<dae::TextureComponent>();
	textureMovable->SetTexture("Pengo_snobee_noBG.png");
	textureMovable->SetSourceRect(0, 0, 16, 16);
	textureMovable->SetWidthAndHeight(TILE_WIDTH, TILE_WIDTH);
	auto pengoC = go->AddComponent<dae::PengoComponent>(200.f, gridC);
	go->SetLocalPosition((GRID_OFSETT.x + (GRID_WIDTH / 2) * TILE_WIDTH), (GRID_OFSETT.y + ((GRID_HEIGHT / 2) - 1) * TILE_WIDTH));
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(SDL_SCANCODE_W, dae::InputType::Keyboard, -1, go.get(), glm::vec3{ 0,-1,0 }, pengoC);
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(SDL_SCANCODE_S, dae::InputType::Keyboard, -1, go.get(), glm::vec3{ 0,1,0 }, pengoC);
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(SDL_SCANCODE_A, dae::InputType::Keyboard, -1, go.get(), glm::vec3{ -1,0,0 }, pengoC);
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(SDL_SCANCODE_D, dae::InputType::Keyboard, -1, go.get(), glm::vec3{ 1,0,0 }, pengoC);
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(XINPUT_GAMEPAD_DPAD_UP, dae::InputType::Controller, 0, go.get(), glm::vec3{ 0,-1,0 }, pengoC);
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(XINPUT_GAMEPAD_DPAD_DOWN, dae::InputType::Controller, 0, go.get(), glm::vec3{ 0,1,0 }, pengoC);
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(XINPUT_GAMEPAD_DPAD_LEFT, dae::InputType::Controller, 0, go.get(), glm::vec3{ -1,0,0 }, pengoC);
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(XINPUT_GAMEPAD_DPAD_RIGHT, dae::InputType::Controller, 0, go.get(), glm::vec3{ 1,0,0 }, pengoC);
	input.AddBinding<dae::PushCommand>(SDL_SCANCODE_E, dae::InputType::Keyboard, 0, go.get(), pengoC);
	input.AddBinding<dae::PushCommand>(XINPUT_GAMEPAD_A, dae::InputType::Controller, 0, go.get(), pengoC);
	scene.Add(go);

	//enemies
	go = std::make_shared<dae::GameObject>();
	auto enemyController = go->AddComponent<dae::EnemyControllerComponent>(gridC);
	enemyController->AddPengo(pengoC);
	enemyController->PlayerControlled(false);
	go->AddObserver(uiObserver);
	scene.Add(go);

	//load
	gridC->LoadLevel(enemyController, 4);
}

void LoadVersus()
{
	const int GRID_WIDTH{ 13 };
	const int GRID_HEIGHT{ 15 };
	const int TILE_WIDTH{ 48 };
	const glm::vec2 GRID_OFSETT{ 24,106 };

	auto& input = dae::InputManager::GetInstance();
	auto& scene = dae::SceneManager::GetInstance().GetScene("Versus");

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
	auto gridC = go->AddComponent<dae::GridComponent>(GRID_WIDTH, GRID_HEIGHT, TILE_WIDTH, GRID_OFSETT, wallComp);
	//gridC->SaveLevel();
	scene.Add(go);

	//text
	go = std::make_shared<dae::GameObject>();
	auto text = go->AddComponent<dae::TextComponent>(font);
	text->SetText("controls: WASD and E or D-PAD and South button");
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	dae::TextureComponent* textureMovable = go->AddComponent<dae::TextureComponent>();
	textureMovable->SetTexture("Pengo_snobee_noBG.png");
	textureMovable->SetSourceRect(0, 0, 16, 16);
	textureMovable->SetWidthAndHeight(TILE_WIDTH, TILE_WIDTH);
	auto pengoC = go->AddComponent<dae::PengoComponent>(200.f, gridC);
	go->SetLocalPosition((GRID_OFSETT.x + (GRID_WIDTH / 2) * TILE_WIDTH), (GRID_OFSETT.y + ((GRID_HEIGHT / 2) - 1) * TILE_WIDTH));
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(SDL_SCANCODE_W, dae::InputType::Keyboard, -1, go.get(), glm::vec3{ 0,-1,0 }, pengoC);
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(SDL_SCANCODE_S, dae::InputType::Keyboard, -1, go.get(), glm::vec3{ 0,1,0 }, pengoC);
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(SDL_SCANCODE_A, dae::InputType::Keyboard, -1, go.get(), glm::vec3{ -1,0,0 }, pengoC);
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(SDL_SCANCODE_D, dae::InputType::Keyboard, -1, go.get(), glm::vec3{ 1,0,0 }, pengoC);
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(XINPUT_GAMEPAD_DPAD_UP, dae::InputType::Controller, 0, go.get(), glm::vec3{ 0,-1,0 }, pengoC);
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(XINPUT_GAMEPAD_DPAD_DOWN, dae::InputType::Controller, 0, go.get(), glm::vec3{ 0,1,0 }, pengoC);
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(XINPUT_GAMEPAD_DPAD_LEFT, dae::InputType::Controller, 0, go.get(), glm::vec3{ -1,0,0 }, pengoC);
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(XINPUT_GAMEPAD_DPAD_RIGHT, dae::InputType::Controller, 0, go.get(), glm::vec3{ 1,0,0 }, pengoC);
	input.AddBinding<dae::PushCommand>(SDL_SCANCODE_E, dae::InputType::Keyboard, 0, go.get(), pengoC);
	input.AddBinding<dae::PushCommand>(XINPUT_GAMEPAD_A, dae::InputType::Controller, 0, go.get(), pengoC);
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	auto enemyController = go->AddComponent<dae::EnemyControllerComponent>(gridC);
	enemyController->AddPengo(pengoC);
	enemyController->PlayerControlled(true);
	input.AddBinding<dae::MoveCommand<dae::EnemyControllerComponent>>(XINPUT_GAMEPAD_DPAD_UP, dae::InputType::Controller, 1, go.get(), glm::vec3{ 0,-1,0 }, enemyController);
	input.AddBinding<dae::MoveCommand<dae::EnemyControllerComponent>>(XINPUT_GAMEPAD_DPAD_DOWN, dae::InputType::Controller, 1, go.get(), glm::vec3{ 0,1,0 }, enemyController);
	input.AddBinding<dae::MoveCommand<dae::EnemyControllerComponent>>(XINPUT_GAMEPAD_DPAD_LEFT, dae::InputType::Controller, 1, go.get(), glm::vec3{ -1,0,0 }, enemyController);
	input.AddBinding<dae::MoveCommand<dae::EnemyControllerComponent>>(XINPUT_GAMEPAD_DPAD_RIGHT, dae::InputType::Controller, 1, go.get(), glm::vec3{ 1,0,0 }, enemyController);
	input.AddBinding<dae::BreakCommand>(XINPUT_GAMEPAD_A, dae::InputType::Controller, 0, go.get(), enemyController);
	scene.Add(go);

	gridC->LoadLevel(enemyController,4);
}

void LoadCoop()
{
	const int GRID_WIDTH{ 13 };
	const int GRID_HEIGHT{ 15 };
	const int TILE_WIDTH{ 48 };
	const glm::vec2 GRID_OFSETT{ 24,106 };

	auto& input = dae::InputManager::GetInstance();
	auto& scene = dae::SceneManager::GetInstance().GetScene("Coop");

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
	auto gridC = go->AddComponent<dae::GridComponent>(GRID_WIDTH, GRID_HEIGHT, TILE_WIDTH, GRID_OFSETT, wallComp);
	scene.Add(go);

	//text
	go = std::make_shared<dae::GameObject>();
	auto text = go->AddComponent<dae::TextComponent>(font);
	text->SetText("controls: WASD and E or D-PAD and South button");
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	dae::TextureComponent* textureMovable = go->AddComponent<dae::TextureComponent>();
	textureMovable->SetTexture("Pengo_snobee_noBG.png");
	textureMovable->SetSourceRect(0, 0, 16, 16);
	textureMovable->SetWidthAndHeight(TILE_WIDTH, TILE_WIDTH);
	auto pengoC = go->AddComponent<dae::PengoComponent>(200.f, gridC);
	go->SetLocalPosition((GRID_OFSETT.x + (GRID_WIDTH / 2) * TILE_WIDTH), (GRID_OFSETT.y + ((GRID_HEIGHT / 2) - 1) * TILE_WIDTH));
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(SDL_SCANCODE_W, dae::InputType::Keyboard, -1, go.get(), glm::vec3{ 0,-1,0 }, pengoC);
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(SDL_SCANCODE_S, dae::InputType::Keyboard, -1, go.get(), glm::vec3{ 0,1,0 }, pengoC);
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(SDL_SCANCODE_A, dae::InputType::Keyboard, -1, go.get(), glm::vec3{ -1,0,0 }, pengoC);
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(SDL_SCANCODE_D, dae::InputType::Keyboard, -1, go.get(), glm::vec3{ 1,0,0 }, pengoC);
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(XINPUT_GAMEPAD_DPAD_UP, dae::InputType::Controller, 0, go.get(), glm::vec3{ 0,-1,0 }, pengoC);
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(XINPUT_GAMEPAD_DPAD_DOWN, dae::InputType::Controller, 0, go.get(), glm::vec3{ 0,1,0 }, pengoC);
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(XINPUT_GAMEPAD_DPAD_LEFT, dae::InputType::Controller, 0, go.get(), glm::vec3{ -1,0,0 }, pengoC);
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(XINPUT_GAMEPAD_DPAD_RIGHT, dae::InputType::Controller, 0, go.get(), glm::vec3{ 1,0,0 }, pengoC);
	input.AddBinding<dae::PushCommand>(SDL_SCANCODE_E, dae::InputType::Keyboard, 0, go.get(), pengoC);
	input.AddBinding<dae::PushCommand>(XINPUT_GAMEPAD_A, dae::InputType::Controller, 0, go.get(), pengoC);
	scene.Add(go);


	go = std::make_shared<dae::GameObject>();
	dae::TextureComponent* textureMovable2 = go->AddComponent<dae::TextureComponent>();
	textureMovable2->SetTexture("Pengo_snobee_noBG.png");
	textureMovable2->SetSourceRect(0, 0, 16, 16);
	textureMovable2->SetWidthAndHeight(TILE_WIDTH, TILE_WIDTH);
	auto pengoC2 = go->AddComponent<dae::PengoComponent>(200.f, gridC);
	go->SetLocalPosition((GRID_OFSETT.x + (GRID_WIDTH / 2) * TILE_WIDTH) - TILE_WIDTH, (GRID_OFSETT.y + ((GRID_HEIGHT / 2) - 1) * TILE_WIDTH));
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(XINPUT_GAMEPAD_DPAD_UP, dae::InputType::Controller, 1, go.get(), glm::vec3{ 0,-1,0 }, pengoC2);
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(XINPUT_GAMEPAD_DPAD_DOWN, dae::InputType::Controller, 1, go.get(), glm::vec3{ 0,1,0 }, pengoC2);
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(XINPUT_GAMEPAD_DPAD_LEFT, dae::InputType::Controller, 1, go.get(), glm::vec3{ -1,0,0 }, pengoC2);
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(XINPUT_GAMEPAD_DPAD_RIGHT, dae::InputType::Controller, 1, go.get(), glm::vec3{ 1,0,0 }, pengoC2);
	input.AddBinding<dae::PushCommand>(XINPUT_GAMEPAD_A, dae::InputType::Controller, 1, go.get(), pengoC2);
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	auto enemyController = go->AddComponent<dae::EnemyControllerComponent>(gridC);
	enemyController->AddPengo(pengoC);
	enemyController->AddPengo(pengoC2);
	enemyController->PlayerControlled(false);
	scene.Add(go);


	gridC->LoadLevel(enemyController, 4);
}

void LoadMain()
{
	auto& input = dae::InputManager::GetInstance();
	auto& scene = dae::SceneManager::GetInstance().GetScene("Main");

	auto go = std::make_shared<dae::GameObject>();
	dae::TextureComponent* textureC1 = go->AddComponent<dae::TextureComponent>();
	textureC1->SetTexture("MainScene.png");
	textureC1->SetWidthAndHeight(672, 840);
	scene.Add(go);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Pengo-Atari 5200.ttf", 20);

	go = std::make_shared<dae::GameObject>();
	auto text = go->AddComponent<dae::TextComponent>(font);
	text->SetText("1 Player only");
	text->SetColor(255, 255, 0);
	go->SetLocalPosition(196, 396);
	scene.Add(go);

	auto startKeyboard = input.AddBinding<dae::StartCommand>(SDL_SCANCODE_E, dae::InputType::Keyboard, -1);
	auto startController = input.AddBinding<dae::StartCommand>(XINPUT_GAMEPAD_START, dae::InputType::Controller, 0);

	input.AddBinding<dae::ChangeGameModeCommand>(SDL_SCANCODE_A, dae::InputType::Keyboard, -1, text, startKeyboard, false);
	input.AddBinding<dae::ChangeGameModeCommand>(XINPUT_GAMEPAD_DPAD_LEFT, dae::InputType::Controller, 0, text, startController, false);

	input.AddBinding<dae::ChangeGameModeCommand>(SDL_SCANCODE_D, dae::InputType::Keyboard, -1, text, startKeyboard, true);
	input.AddBinding<dae::ChangeGameModeCommand>(XINPUT_GAMEPAD_DPAD_RIGHT, dae::InputType::Controller, 0, text, startController, true);
}

int main(int, char* []) {

	dae::SceneManager::GetInstance().CreateScene("Main", LoadMain);
	dae::SceneManager::GetInstance().CreateScene("Pengo", LoadPengo);
	dae::SceneManager::GetInstance().CreateScene("Versus", LoadVersus);
	dae::SceneManager::GetInstance().CreateScene("Coop", LoadCoop);

	dae::ServiceLocator::GetInstance().RegisterSoundSystem(std::make_unique<dae::MixerSoundSystem>());

	dae::ServiceLocator::GetInstance().GetSoundSystem().LoadMusic(static_cast<dae::sound_id>(dae::make_sdbm_hash("BGMusic")), "../Data/PengoSoundFX/Main_BGM_Popcorn.mp3");
	dae::ServiceLocator::GetInstance().GetSoundSystem().PlayLooping(static_cast<dae::sound_id>(dae::make_sdbm_hash("BGMusic")), 10.f,-1);

	dae::Minigin engine("../Data/", 672, 840);
	engine.Run(LoadMain);

	return 0;
}