#pragma once
class CppBehaviour
{
public:
	CppBehaviour();

	virtual void Update(float deltaTime);
	virtual void Render() const;

	virtual ~CppBehaviour() = default;
	CppBehaviour(const CppBehaviour& other) = delete;
	CppBehaviour(CppBehaviour&& other) = delete;
	CppBehaviour& operator=(const CppBehaviour& other) = delete;
	CppBehaviour& operator=(CppBehaviour&& other) = delete;
private:

};

