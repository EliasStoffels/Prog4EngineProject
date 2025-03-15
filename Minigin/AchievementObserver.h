#pragma once
#include "CppBehaviour.h"
#include "BaseObserver.h"

namespace dae
{
	class AchievementComponent : public CppBehaviour, public Observer
	{
		friend class GameObject;

	public:
		virtual void Notify(const Event& event, GameObject* object);

		virtual ~AchievementComponent() = default;
		AchievementComponent(const AchievementComponent& other) = delete;
		AchievementComponent(AchievementComponent&& other) = delete;
		AchievementComponent& operator=(const AchievementComponent& other) = delete;
		AchievementComponent& operator=(AchievementComponent&& other) = delete;

	private:
		AchievementComponent();
		bool hasAchieved = false;
	};
}





