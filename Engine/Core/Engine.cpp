#include "Engine.h"
#include <iostream>


Engine::Engine()
{
}

Engine::~Engine()
{
}

void Engine::Run()
{
	// 밀리 세컨드 단위로 시간을 알려줌
	//float currentTime = timeGetTime();
	LARGE_INTEGER currentTime;
	LARGE_INTEGER previousTime;
	QueryPerformanceCounter(&currentTime);
	previousTime = currentTime;

	// 하드웨어 시계의 정밀도(주파수) 가져오기 : 나중에 초로 변환하기 위해
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	float targetFrameRate = 60.0f;	// 타겟 프레임
	float oneFrameTime = 1.0f / targetFrameRate;	// 타겟 한 프레임 시간

	while (true)
	{
		if (isQuit)
		{
			break;
		}

		// 프레임 시간 계산 : (현재 시간 - 이전 시간) / 주파수 = 초단위
		QueryPerformanceCounter(&currentTime);
		float deltaTime = (currentTime.QuadPart - previousTime.QuadPart) / (float)frequency.QuadPart;

		// 입력은 최대한 빨리
		ProcessInput();

		// 고정프레임
		if (deltaTime >= oneFrameTime) 
		{
			Update(deltaTime);
			Render();

			// 시간 업데이트
			previousTime = currentTime;
		}
	}
}

void Engine::Quit()
{
	isQuit = true;
}

void Engine::ProcessInput()
{
	// ESC키 눌림 확인
	// 0x8000 : 이전에 누른 적이 없고 호출 시점에는 눌려있는 상태
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) 
	{
		Quit();
	}
}

void Engine::Update(float deltaTime)
{
	std::cout
		<< "DeltaTime: " << deltaTime
		<< ", FPS: " << (1.0f / deltaTime)
		<< "\n";
}

void Engine::Render()
{

}
