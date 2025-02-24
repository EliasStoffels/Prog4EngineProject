#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

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

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	//create gameObject
	auto go = std::make_shared<dae::GameObject>();

	auto fpsGo = std::make_shared<dae::GameObject>();

	//add components

	//textures
	dae::TextureComponent* textureC1 = go->AddComponent<dae::TextureComponent>();
	textureC1->SetTexture("background.tga");
	scene.Add(go);
	
	go = std::make_shared<dae::GameObject>();
	dae::TextureComponent* textureC2 = go->AddComponent<dae::TextureComponent>();
	textureC2->SetTexture("logo.tga");
	go->SetLocalPosition(216, 180);
	scene.Add(go);

	// root Game Object;
	auto rootGo = std::make_shared<dae::GameObject>();
	rootGo->SetLocalPosition(500, 300);
	scene.Add(rootGo);

	// parent game object
	auto parentGo = std::make_shared<dae::GameObject>();
	dae::TextureComponent* textureTemp = parentGo->AddComponent<dae::TextureComponent>();
	textureTemp->SetTexture("pengo.tga");
	dae::RotateComponent* parentRotatec = parentGo->AddComponent<dae::RotateComponent>();
	parentRotatec->SetRadius(30.f);
	parentRotatec->SetRadianPerSecond(static_cast<float>(M_PI));
	parentGo->SetParent(rootGo.get(), false);
	scene.Add(parentGo);

	// child game object
	go = std::make_shared<dae::GameObject>();
	dae::TextureComponent* textureC3 = go->AddComponent<dae::TextureComponent>();
	textureC3->SetTexture("pengo.tga");
	dae::RotateComponent* rotatec = go->AddComponent<dae::RotateComponent>();
	rotatec->SetRadius(30.f);
	rotatec->SetRadianPerSecond(static_cast<float>(-M_PI/2));
	go->SetLocalPosition(30, 30);
	go->SetParent(parentGo.get(), false);
	scene.Add(go);

	 
	//text
	go = std::make_shared<dae::GameObject>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	dae::TextComponent* tc = go->AddComponent<dae::TextComponent>();
	tc->SetFont(font);
	tc->SetText("Programming 4 Assignment");
	go->SetLocalPosition(80, 20);
	scene.Add(go);
	
	//fps
	fpsGo->AddComponent<dae::FpsComponent>();
	dae::TextComponent* tcFps = fpsGo->AddComponent<dae::TextComponent>();
	tcFps->SetFont(font);
	tcFps->SetText("number");
	scene.Add(fpsGo);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}