#pragma once
#include "CppBehaviour.h"

namespace dae
{
	class TextComponent;

	class FpsComponent : public CppBehaviour
	{
		friend class GameObject;

	public:
		void Start();
		void Update(float deltaTime) override;
		
		virtual ~FpsComponent() = default;
		FpsComponent(const FpsComponent& other) = delete;
		FpsComponent(FpsComponent&& other) = delete;
		FpsComponent& operator=(const FpsComponent& other) = delete;
		FpsComponent& operator=(FpsComponent&& other) = delete;

	private:
		FpsComponent();
		float m_fpsUpdateDelay{1/10.f};
		float m_totalDeltaTime{};
		TextComponent* m_TextComp = nullptr;
	};
}

