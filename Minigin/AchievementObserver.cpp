#include "AchievementObserver.h"

#include <SteamAchievements.h>
#include <iostream>

dae::AchievementComponent::AchievementComponent()
{
}


void dae::AchievementComponent::Notify(const Event& event, GameObject*)
{
	if (event.id == sdbm_hash("ScoreChanged"))
	{
		if (reinterpret_cast<ScoreChangedArgs*>(event.arg)->newScore >= 500 && !hasAchieved)
		{
			hasAchieved = true;
			UnlockAchievement("ACH_WIN_ONE_GAME");
		}
	}
}
