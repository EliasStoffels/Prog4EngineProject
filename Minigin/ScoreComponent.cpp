#include "ScoreComponent.h"
#include "GameObject.h"
#include "BaseObserver.h"
#include <AchievementObserver.h>

namespace dae
{

	ScoreComponent::ScoreComponent()
	{

	}

	void ScoreComponent::ChangeScore(int value)
	{
		m_Score += value;
		ScoreChangedArgs args = ScoreChangedArgs{ m_Score };
		m_OwningGameObject->NotifyObservers(Event{ sdbm_hash("ScoreChanged"), &args});
	}
}
