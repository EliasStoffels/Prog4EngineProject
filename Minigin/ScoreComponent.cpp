#include "ScoreComponent.h"
#include "GameObject.h"
#include "BaseObserver.h"

namespace dae
{

	ScoreComponent::ScoreComponent()
	{

	}

	void ScoreComponent::ChangeScore(int value)
	{
		m_Score += value;
		ScoreChangedArgs args = ScoreChangedArgs(value);
		m_OwningGameObject->NotifyObservers(Event{ sdbm_hash("ScoreChanged"), &args});
	}
}
