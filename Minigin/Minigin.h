#pragma once
#include <string>
#include <functional>

namespace dae
{
	class Minigin
	{
	public:
		explicit Minigin(const std::string& dataPath, int x, int y);
		~Minigin();
		void RunOneFrame();
		void Run(const std::string& scene);

		Minigin(const Minigin& other) = delete;
		Minigin(Minigin&& other) = delete;
		Minigin& operator=(const Minigin& other) = delete;
		Minigin& operator=(Minigin&& other) = delete;

	private:
		int msPerFrame{16};
		float fixedTimeStep{ 1.f / 60.f };
		int m_ScreenX = 800;
		int m_ScreenY = 600;

	};
}