#pragma once

namespace dae
{
	class GameObject;

	class CppBehaviour
	{
	public:
		CppBehaviour();

		virtual void Start();

		virtual void Update(float deltaTime);
		virtual void Render() const;

		virtual ~CppBehaviour() = default;
		CppBehaviour(const CppBehaviour& other) = delete;
		CppBehaviour(CppBehaviour&& other) = delete;
		CppBehaviour& operator=(const CppBehaviour& other) = delete;
		CppBehaviour& operator=(CppBehaviour&& other) = delete;
		void SetOwningGameObject(GameObject* owningGameObject);

		bool pendingRemove = false;
	private:

	protected:
		GameObject* m_OwningGameObject{ nullptr };
	};
}

