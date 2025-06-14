#pragma once

namespace dae
{
	class GameObject;

	class CppBehaviour
	{
		friend class GameObject;
	public:
		virtual void Start();

		virtual void Update(float deltaTime);
		virtual void FixedUpdate(float fixedTime);
		virtual void LateUpdate(float deltaTime);
		virtual void Render() const;
		GameObject* GetOwner()
		{
			return m_OwningGameObject;
		}

		virtual ~CppBehaviour() = default;
		CppBehaviour(const CppBehaviour& other) = delete;
		CppBehaviour(CppBehaviour&& other) = delete;
		CppBehaviour& operator=(const CppBehaviour& other) = delete;
		CppBehaviour& operator=(CppBehaviour&& other) = delete;

		bool pendingRemove = false;
	private:
		void SetOwningGameObject(GameObject& owningGameObject);
		bool m_StartWasCalled = false;
	protected:
		CppBehaviour(GameObject* owner);
		GameObject* m_OwningGameObject{ nullptr };
	};
}

