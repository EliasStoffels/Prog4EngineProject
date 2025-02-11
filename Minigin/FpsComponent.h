#pragma once
#include "CppBehaviour.h"

namespace dae
{
	class FpsComponent : public CppBehaviour
	{
	public:
		void Start();
		void Update(float deltaTime) override;

		FpsComponent();
		virtual ~FpsComponent() = default;
		FpsComponent(const FpsComponent& other) = delete;
		FpsComponent(FpsComponent&& other) = delete;
		FpsComponent& operator=(const FpsComponent& other) = delete;
		FpsComponent& operator=(FpsComponent&& other) = delete;
	private:
		float m_fpsUpdateDelay{1/10.f};
		float m_totalDeltaTime{};
	};
}

