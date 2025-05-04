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

		virtual ~CppBehaviour() = default;
		CppBehaviour(const CppBehaviour& other) = delete;
		CppBehaviour(CppBehaviour&& other) = delete;
		CppBehaviour& operator=(const CppBehaviour& other) = delete;
		CppBehaviour& operator=(CppBehaviour&& other) = delete;

		bool pendingRemove = false;
	private:
		void SetOwningGameObject(GameObject& owningGameObject);
	protected:
		CppBehaviour();
		GameObject* m_OwningGameObject{ nullptr };
	};
}

