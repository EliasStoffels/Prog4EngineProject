#pragma once
#include "CppBehaviour.h"

namespace dae
{
	class ScoreComponent : public CppBehaviour
	{
		friend class GameObject;

	public:
		void ChangeScore(int value);

		virtual ~ScoreComponent() = default;
		ScoreComponent(const ScoreComponent& other) = delete;
		ScoreComponent(ScoreComponent&& other) = delete;
		ScoreComponent& operator=(const ScoreComponent& other) = delete;
		ScoreComponent& operator=(ScoreComponent&& other) = delete;

	private:
		ScoreComponent();
		int m_Score = 0;
	};
}

