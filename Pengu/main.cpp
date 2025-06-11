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
#include "RespawnCommand.h"
#include "GameStateManager.h"

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
	auto background = scene.AddEmpty();
	dae::TextureComponent* textureC1 = background->AddComponent<dae::TextureComponent>();
	textureC1->SetTexture("BlackBG.png");
	textureC1->SetWidthAndHeight(672, 768);
	background->SetLocalPosition(0, 82);

	//walls
	auto walls = scene.AddEmpty();
	auto vertWallTex = walls->AddComponent<dae::TextureComponent>();
	vertWallTex->SetTexture("VerticalWallTex.png");
	vertWallTex->IsActive(false);
	auto horWallTex = walls->AddComponent<dae::TextureComponent>();
	horWallTex->SetTexture("HorizontalWallTex.png");
	horWallTex->IsActive(false);
	auto wallComp = walls->AddComponent<dae::WallComponent>(GRID_OFSETT, glm::vec2{ GRID_WIDTH * TILE_WIDTH, GRID_HEIGHT * TILE_WIDTH }, vertWallTex, horWallTex);

	//grid
	auto grid = scene.AddEmpty();
	auto gridC = grid->AddComponent<dae::GridComponent>(GRID_WIDTH,GRID_HEIGHT,TILE_WIDTH,GRID_OFSETT, wallComp);
	gridC->SaveLevel();

	//static ui
	auto staticUi = scene.AddEmpty();
	dae::TextureComponent* textureSaticUi = staticUi->AddComponent<dae::TextureComponent>();
	textureSaticUi->SetTexture("StaticUi.png");
	textureSaticUi->SetWidthAndHeight(672, 20);
	
	// dynamic ui
	auto dynamicUi = scene.AddEmpty();
	auto uiObserver = dynamicUi->AddComponent<dae::UIObserverComponent>();
	dynamicUi->SetLocalPosition(0, 0, 1000); // put infornt of everything

	//pengo
	auto pengo = scene.AddEmpty();
	dae::TextureComponent* textureMovable = pengo->AddComponent<dae::TextureComponent>();
	textureMovable->SetTexture("Pengo_snobee_noBG.png");
	textureMovable->SetSourceRect(0, 0, 16, 16);
	textureMovable->SetWidthAndHeight(TILE_WIDTH, TILE_WIDTH);
	auto pengoC = pengo->AddComponent<dae::PengoComponent>(200.f, gridC);
	pengo->SetLocalPosition((GRID_OFSETT.x + (GRID_WIDTH / 2) * TILE_WIDTH), (GRID_OFSETT.y + ((GRID_HEIGHT / 2) - 1) * TILE_WIDTH));
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(SDL_SCANCODE_W, dae::InputType::Keyboard, 0, glm::vec3{ 0,-1,0 }, pengoC);
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(SDL_SCANCODE_S, dae::InputType::Keyboard, 0, glm::vec3{ 0,1,0 }, pengoC);
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(SDL_SCANCODE_A, dae::InputType::Keyboard, 0, glm::vec3{ -1,0,0 }, pengoC);
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(SDL_SCANCODE_D, dae::InputType::Keyboard, 0, glm::vec3{ 1,0,0 }, pengoC);
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(XINPUT_GAMEPAD_DPAD_UP, dae::InputType::Controller, 0, glm::vec3{ 0,-1,0 }, pengoC);
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(XINPUT_GAMEPAD_DPAD_DOWN, dae::InputType::Controller, 0, glm::vec3{ 0,1,0 }, pengoC);
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(XINPUT_GAMEPAD_DPAD_LEFT, dae::InputType::Controller, 0, glm::vec3{ -1,0,0 }, pengoC);
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(XINPUT_GAMEPAD_DPAD_RIGHT, dae::InputType::Controller, 0, glm::vec3{ 1,0,0 }, pengoC);
	input.AddBinding<dae::PushCommand>(SDL_SCANCODE_E, dae::InputType::Keyboard, 0, pengoC);
	input.AddBinding<dae::PushCommand>(XINPUT_GAMEPAD_A, dae::InputType::Controller, 0, pengoC);

	//enemies
	auto enemies = scene.AddEmpty();
	auto enemyController = enemies->AddComponent<dae::EnemyControllerComponent>(gridC);
	enemyController->AddPengo(pengoC);
	enemyController->PlayerControlled(false);
	enemies->AddObserver(uiObserver);
	enemies->AddObserver(&dae::GameStateManager::GetInstance());


	//respawn
	auto respawnGo = scene.AddEmpty();
	input.AddBinding<dae::RespawnCommand>(SDL_SCANCODE_E, dae::InputType::Keyboard, 0, respawnGo);
	input.AddBinding<dae::RespawnCommand>(XINPUT_GAMEPAD_START, dae::InputType::Controller, 0, respawnGo);
	respawnGo->AddObserver(pengoC);
	respawnGo->AddObserver(uiObserver);
	respawnGo->AddObserver(enemyController);


	//load
	gridC->LoadLevel(enemyController, dae::GameStateManager::GetInstance().GetLevel());
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
	auto background = scene.AddEmpty();
	dae::TextureComponent* textureC1 = background->AddComponent<dae::TextureComponent>();
	textureC1->SetTexture("BlackBG.png");
	textureC1->SetWidthAndHeight(672, 768);
	background->SetLocalPosition(0, 82);

	//walls
	auto walls = scene.AddEmpty();
	auto vertWallTex = walls->AddComponent<dae::TextureComponent>();
	vertWallTex->SetTexture("VerticalWallTex.png");
	vertWallTex->IsActive(false);
	auto horWallTex = walls->AddComponent<dae::TextureComponent>();
	horWallTex->SetTexture("HorizontalWallTex.png");
	horWallTex->IsActive(false);
	auto wallComp = walls->AddComponent<dae::WallComponent>(GRID_OFSETT, glm::vec2{ GRID_WIDTH * TILE_WIDTH, GRID_HEIGHT * TILE_WIDTH }, vertWallTex, horWallTex);

	//grid
	auto grid = scene.AddEmpty();
	auto gridC = grid->AddComponent<dae::GridComponent>(GRID_WIDTH, GRID_HEIGHT, TILE_WIDTH, GRID_OFSETT, wallComp);
	//gridC->SaveLevel();

	//text
	auto controlltext = scene.AddEmpty();
	auto text = controlltext->AddComponent<dae::TextComponent>(font);
	text->SetText("controls: WASD and E or D-PAD and South button");

	auto pengo = scene.AddEmpty();
	dae::TextureComponent* textureMovable = pengo->AddComponent<dae::TextureComponent>();
	textureMovable->SetTexture("Pengo_snobee_noBG.png");
	textureMovable->SetSourceRect(0, 0, 16, 16);
	textureMovable->SetWidthAndHeight(TILE_WIDTH, TILE_WIDTH);
	auto pengoC = pengo->AddComponent<dae::PengoComponent>(200.f, gridC);
	pengo->SetLocalPosition((GRID_OFSETT.x + (GRID_WIDTH / 2) * TILE_WIDTH), (GRID_OFSETT.y + ((GRID_HEIGHT / 2) - 1) * TILE_WIDTH));
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(SDL_SCANCODE_W, dae::InputType::Keyboard, -1, glm::vec3{ 0,-1,0 }, pengoC);
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(SDL_SCANCODE_S, dae::InputType::Keyboard, -1, glm::vec3{ 0,1,0 }, pengoC);
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(SDL_SCANCODE_A, dae::InputType::Keyboard, -1, glm::vec3{ -1,0,0 }, pengoC);
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(SDL_SCANCODE_D, dae::InputType::Keyboard, -1, glm::vec3{ 1,0,0 }, pengoC);
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(XINPUT_GAMEPAD_DPAD_UP, dae::InputType::Controller, 0, glm::vec3{ 0,-1,0 }, pengoC);
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(XINPUT_GAMEPAD_DPAD_DOWN, dae::InputType::Controller, 0, glm::vec3{ 0,1,0 }, pengoC);
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(XINPUT_GAMEPAD_DPAD_LEFT, dae::InputType::Controller, 0, glm::vec3{ -1,0,0 }, pengoC);
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(XINPUT_GAMEPAD_DPAD_RIGHT, dae::InputType::Controller, 0, glm::vec3{ 1,0,0 }, pengoC);
	input.AddBinding<dae::PushCommand>(SDL_SCANCODE_E, dae::InputType::Keyboard, 0, pengoC);
	input.AddBinding<dae::PushCommand>(XINPUT_GAMEPAD_A, dae::InputType::Controller, 0,  pengoC);

	auto enemies = scene.AddEmpty();
	auto enemyController = enemies->AddComponent<dae::EnemyControllerComponent>(gridC);
	enemyController->AddPengo(pengoC);
	enemyController->PlayerControlled(true);
	input.AddBinding<dae::MoveCommand<dae::EnemyControllerComponent>>(XINPUT_GAMEPAD_DPAD_UP, dae::InputType::Controller, 1, glm::vec3{ 0,-1,0 }, enemyController);
	input.AddBinding<dae::MoveCommand<dae::EnemyControllerComponent>>(XINPUT_GAMEPAD_DPAD_DOWN, dae::InputType::Controller, 1, glm::vec3{ 0,1,0 }, enemyController);
	input.AddBinding<dae::MoveCommand<dae::EnemyControllerComponent>>(XINPUT_GAMEPAD_DPAD_LEFT, dae::InputType::Controller, 1, glm::vec3{ -1,0,0 }, enemyController);
	input.AddBinding<dae::MoveCommand<dae::EnemyControllerComponent>>(XINPUT_GAMEPAD_DPAD_RIGHT, dae::InputType::Controller, 1, glm::vec3{ 1,0,0 }, enemyController);
	input.AddBinding<dae::BreakCommand>(XINPUT_GAMEPAD_A, dae::InputType::Controller, 0, enemyController);

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
	auto go = scene.AddEmpty();
	dae::TextureComponent* textureC1 = go->AddComponent<dae::TextureComponent>();
	textureC1->SetTexture("BlackBG.png");
	textureC1->SetWidthAndHeight(672, 768);
	go->SetLocalPosition(0, 82);

	//walls
	go = scene.AddEmpty();
	auto vertWallTex = go->AddComponent<dae::TextureComponent>();
	vertWallTex->SetTexture("VerticalWallTex.png");
	vertWallTex->IsActive(false);
	auto horWallTex = go->AddComponent<dae::TextureComponent>();
	horWallTex->SetTexture("HorizontalWallTex.png");
	horWallTex->IsActive(false);
	auto wallComp = go->AddComponent<dae::WallComponent>(GRID_OFSETT, glm::vec2{ GRID_WIDTH * TILE_WIDTH, GRID_HEIGHT * TILE_WIDTH }, vertWallTex, horWallTex);

	//grid
	go = scene.AddEmpty();
	auto gridC = go->AddComponent<dae::GridComponent>(GRID_WIDTH, GRID_HEIGHT, TILE_WIDTH, GRID_OFSETT, wallComp);

	//text
	go = scene.AddEmpty();
	auto text = go->AddComponent<dae::TextComponent>(font);
	text->SetText("controls: WASD and E or D-PAD and South button");

	go = scene.AddEmpty();
	dae::TextureComponent* textureMovable = go->AddComponent<dae::TextureComponent>();
	textureMovable->SetTexture("Pengo_snobee_noBG.png");
	textureMovable->SetSourceRect(0, 0, 16, 16);
	textureMovable->SetWidthAndHeight(TILE_WIDTH, TILE_WIDTH);
	auto pengoC = go->AddComponent<dae::PengoComponent>(200.f, gridC);
	go->SetLocalPosition((GRID_OFSETT.x + (GRID_WIDTH / 2) * TILE_WIDTH), (GRID_OFSETT.y + ((GRID_HEIGHT / 2) - 1) * TILE_WIDTH));
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(SDL_SCANCODE_W, dae::InputType::Keyboard, -1, glm::vec3{ 0,-1,0 }, pengoC);
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(SDL_SCANCODE_S, dae::InputType::Keyboard, -1, glm::vec3{ 0,1,0 }, pengoC);
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(SDL_SCANCODE_A, dae::InputType::Keyboard, -1, glm::vec3{ -1,0,0 }, pengoC);
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(SDL_SCANCODE_D, dae::InputType::Keyboard, -1, glm::vec3{ 1,0,0 }, pengoC);
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(XINPUT_GAMEPAD_DPAD_UP, dae::InputType::Controller, 0, glm::vec3{ 0,-1,0 }, pengoC);
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(XINPUT_GAMEPAD_DPAD_DOWN, dae::InputType::Controller, 0, glm::vec3{ 0,1,0 }, pengoC);
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(XINPUT_GAMEPAD_DPAD_LEFT, dae::InputType::Controller, 0, glm::vec3{ -1,0,0 }, pengoC);
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(XINPUT_GAMEPAD_DPAD_RIGHT, dae::InputType::Controller, 0, glm::vec3{ 1,0,0 }, pengoC);
	input.AddBinding<dae::PushCommand>(SDL_SCANCODE_E, dae::InputType::Keyboard, 0, pengoC);
	input.AddBinding<dae::PushCommand>(XINPUT_GAMEPAD_A, dae::InputType::Controller, 0, pengoC);


	go = scene.AddEmpty();
	dae::TextureComponent* textureMovable2 = go->AddComponent<dae::TextureComponent>();
	textureMovable2->SetTexture("Pengo_snobee_noBG.png");
	textureMovable2->SetSourceRect(0, 0, 16, 16);
	textureMovable2->SetWidthAndHeight(TILE_WIDTH, TILE_WIDTH);
	auto pengoC2 = go->AddComponent<dae::PengoComponent>(200.f, gridC);
	go->SetLocalPosition((GRID_OFSETT.x + (GRID_WIDTH / 2) * TILE_WIDTH) - TILE_WIDTH, (GRID_OFSETT.y + ((GRID_HEIGHT / 2) - 1) * TILE_WIDTH));
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(XINPUT_GAMEPAD_DPAD_UP, dae::InputType::Controller, 1, glm::vec3{ 0,-1,0 }, pengoC2);
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(XINPUT_GAMEPAD_DPAD_DOWN, dae::InputType::Controller, 1, glm::vec3{ 0,1,0 }, pengoC2);
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(XINPUT_GAMEPAD_DPAD_LEFT, dae::InputType::Controller, 1, glm::vec3{ -1,0,0 }, pengoC2);
	input.AddBinding<dae::MoveCommand<dae::PengoComponent>>(XINPUT_GAMEPAD_DPAD_RIGHT, dae::InputType::Controller, 1, glm::vec3{ 1,0,0 }, pengoC2);
	input.AddBinding<dae::PushCommand>(XINPUT_GAMEPAD_A, dae::InputType::Controller, 1, pengoC2);

	go = scene.AddEmpty();
	auto enemyController = go->AddComponent<dae::EnemyControllerComponent>(gridC);
	enemyController->AddPengo(pengoC);
	enemyController->AddPengo(pengoC2);
	enemyController->PlayerControlled(false);


	gridC->LoadLevel(enemyController, 4);
}

void LoadMain()
{
	auto& input = dae::InputManager::GetInstance();
	auto& scene = dae::SceneManager::GetInstance().GetScene("Main");

	auto staticUi = scene.AddEmpty();
	dae::TextureComponent* textureSaticUi = staticUi->AddComponent<dae::TextureComponent>();
	textureSaticUi->SetTexture("StaticUi.png");
	textureSaticUi->SetWidthAndHeight(672, 20);

	auto go = scene.AddEmpty();
	dae::TextureComponent* textureC1 = go->AddComponent<dae::TextureComponent>();
	textureC1->SetTexture("MainScene.png");
	textureC1->SetWidthAndHeight(672, 840);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Pengo-Atari 5200.ttf", 20);

	go = scene.AddEmpty();
	auto text = go->AddComponent<dae::TextComponent>(font);
	text->SetText("1 Player only");
	text->SetColor(255, 255, 0);
	go->SetLocalPosition(196, 396, 1000);

	auto startKeyboard = input.AddBinding<dae::StartCommand>(SDL_SCANCODE_E, dae::InputType::Keyboard, -1);
	auto startController = input.AddBinding<dae::StartCommand>(XINPUT_GAMEPAD_START, dae::InputType::Controller, 0);

	input.AddBinding<dae::ChangeGameModeCommand>(SDL_SCANCODE_A, dae::InputType::Keyboard, -1, text, startKeyboard, false);
	input.AddBinding<dae::ChangeGameModeCommand>(XINPUT_GAMEPAD_DPAD_LEFT, dae::InputType::Controller, 0, text, startController, false);

	input.AddBinding<dae::ChangeGameModeCommand>(SDL_SCANCODE_D, dae::InputType::Keyboard, -1, text, startKeyboard, true);
	input.AddBinding<dae::ChangeGameModeCommand>(XINPUT_GAMEPAD_DPAD_RIGHT, dae::InputType::Controller, 0, text, startController, true);

}

void LoadScoreScene()
{
	auto& input = dae::InputManager::GetInstance();
	auto& scene = dae::SceneManager::GetInstance().GetScene("ScoreScene");

	auto font = dae::ResourceManager::GetInstance().LoadFont("Pengo-Atari 5200.ttf", 25);
	auto smallFont = dae::ResourceManager::GetInstance().LoadFont("Pengo-Atari 5200.ttf", 20);

	auto staticUi = scene.AddEmpty();
	auto textureLives = staticUi->AddComponent<dae::TextureComponent>();
	textureLives->SetTexture("Misc.png");
	textureLives->SetWidthAndHeight(48, 48);
	textureLives->SetSourceRect(0, 150, 16, 16);
	textureLives->SetRepeats(dae::GameStateManager::GetInstance().GetLives());
	textureLives->SetRepeatOfsett(glm::vec3{ 50,0,0 });
	textureLives->SetRenderOfsett(glm::vec3{ 20,30,0 });

	dae::TextureComponent* textureSaticUi = staticUi->AddComponent<dae::TextureComponent>();
	textureSaticUi->SetTexture("StaticUi.png");
	textureSaticUi->SetWidthAndHeight(672, 20);

	auto textPoints = staticUi->AddComponent<dae::TextComponent>(smallFont);
	textPoints->SetRenderOfSet(glm::vec3{ 340,2,0 });
	textPoints->SetText(std::to_string(dae::GameStateManager::GetInstance().GetScore()));

	auto go = scene.AddEmpty();
	auto text = go->AddComponent<dae::TextComponent>(font);
	text->SetText("GAME TIME					MIN.		SEC.");
	text->SetColor(255, 255, 0);

	text->SetRenderOfSet(glm::vec3{ 40, 150 ,0});

	text = go->AddComponent<dae::TextComponent>(font);
	text->SetText("FROM 00 TO 19 .5000 PTS");
	text->SetColor(0, 255, 255);
	text->SetRenderOfSet(glm::vec3{ 40, 200 ,0 });

	text = go->AddComponent<dae::TextComponent>(font);
	text->SetText("FROM 20 TO 29 .2000 PTS");
	text->SetColor(0, 255, 255);
	text->SetRenderOfSet(glm::vec3{ 40, 250 ,0 });

	text = go->AddComponent<dae::TextComponent>(font);
	text->SetText("FROM 30 TO 39 .1000 PTS");
	text->SetColor(0, 255, 255);
	text->SetRenderOfSet(glm::vec3{ 40, 300 ,0 });

	text = go->AddComponent<dae::TextComponent>(font);
	text->SetText("FROM 40 TO 49 ..500 PTS");
	text->SetColor(0, 255, 255);
	text->SetRenderOfSet(glm::vec3{ 40, 350 ,0 });

	text = go->AddComponent<dae::TextComponent>(font);
	text->SetText("FROM 50 TO 59 ...10 PTS");
	text->SetColor(0, 255, 255);
	text->SetRenderOfSet(glm::vec3{ 40, 400 ,0 });

	text = go->AddComponent<dae::TextComponent>(font);
	text->SetText("60 AND OVER				NO BONUS");
	text->SetColor(255, 255, 0);
	text->SetRenderOfSet(glm::vec3{ 40, 450 ,0 });

	auto textTime = go->AddComponent<dae::TextComponent>(font);
	textTime->SetRenderOfSet(glm::vec3{ 355,150,0 });
	float levelTimeSeconds = dae::GameStateManager::GetInstance().GetLevelTime();

	int minutes = static_cast<int>(levelTimeSeconds) / 60;
	int seconds = static_cast<int>(levelTimeSeconds) % 60;

	std::string timeText = std::to_string(minutes) + "				" +
		(seconds < 10 ? "0" : "") + std::to_string(seconds);

	textTime->SetText(timeText);

	input.AddBinding<dae::StartCommand>(SDL_SCANCODE_E, dae::InputType::Keyboard, -1);
	input.AddBinding<dae::StartCommand>(XINPUT_GAMEPAD_START, dae::InputType::Controller, 0);

	go->SetLocalPosition(0, 0, FLT_MAX);
}

void LoadHighScore()
{

}

int main(int, char* []) {

	dae::SceneManager::GetInstance().CreateScene("Main", LoadMain);
	dae::SceneManager::GetInstance().CreateScene("Pengo", LoadPengo);
	dae::SceneManager::GetInstance().CreateScene("Versus", LoadVersus);
	dae::SceneManager::GetInstance().CreateScene("Coop", LoadCoop);
	dae::SceneManager::GetInstance().CreateScene("ScoreScene", LoadScoreScene);
	dae::SceneManager::GetInstance().CreateScene("HighScoreScene", LoadHighScore);

	dae::ServiceLocator::GetInstance().RegisterSoundSystem(std::make_unique<dae::MixerSoundSystem>());

	dae::ServiceLocator::GetInstance().GetSoundSystem().LoadMusic(static_cast<dae::sound_id>(dae::make_sdbm_hash("BGMusic")), "../Data/PengoSoundFX/Main_BGM_Popcorn.mp3");
	dae::ServiceLocator::GetInstance().GetSoundSystem().PlayLooping(static_cast<dae::sound_id>(dae::make_sdbm_hash("BGMusic")), 10.f,-1);

	dae::Minigin engine("../Data/", 672, 840);
	engine.Run("Main");

	return 0;
}