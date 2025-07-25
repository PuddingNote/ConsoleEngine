#include <iostream>
#include "Engine.h"
#include "Level/Level.h"
#include <Windows.h>

// 정적 변수 호기화
Engine* Engine::instance = nullptr;

Engine::Engine()
{
	instance = this;

	CONSOLE_CURSOR_INFO info;
	info.bVisible = false;
	info.dwSize = 1;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	
}

Engine::~Engine()
{
	if (mainLevel != nullptr)
	{
		delete mainLevel;
		mainLevel = nullptr;
	}
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

	float targetFrameRate = 60.0f;					// 타겟 프레임
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
			BeginPlay();
			Tick(deltaTime);
			Render();

			// 시간 업데이트
			previousTime = currentTime;
		
			// 현재 프레임의 입력을 기록
			for (int i = 0; i < 255; ++i)
			{
				keyStates[i].previousKeyDown = keyStates[i].isKeyDown;
			}
		}
	}

	// 정리 (게임 종료시 실행)
	


	// 모든 텍스트 색상 변경
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void Engine::Quit()
{
	isQuit = true;
}

bool Engine::GetKey(int keyCode)
{
	return keyStates[keyCode].isKeyDown;
}

bool Engine::GetKeyDown(int keyCode)
{
	return !keyStates[keyCode].previousKeyDown 
		&& keyStates[keyCode].isKeyDown;
}

bool Engine::GetKeyUp(int keyCode)
{
	return keyStates[keyCode].previousKeyDown
		&& !keyStates[keyCode].isKeyDown;
}

void Engine::AddLevel(Level* newLevel)
{
	if (mainLevel != nullptr)
	{
		delete mainLevel;
	}

	mainLevel = newLevel;
}

Engine& Engine::Get()
{
	return *instance;
}

void Engine::ProcessInput()
{
	// 키 입력 확인
	for (int i = 0; i < 255; ++i)
	{
		keyStates[i].isKeyDown = GetAsyncKeyState(i) & 0x8000;
	}

	// ESC키 눌림 확인
	// 0x8000 : 이전에 누른 적이 없고 호출 시점에는 눌려있는 상태
	/*if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) 
	{
		Quit();
	}*/
}

void Engine::BeginPlay()
{
	if (mainLevel != nullptr)
	{
		mainLevel->BeginPlay();
	}
}

void Engine::Tick(float deltaTime)
{
	/*std::cout
		<< "DeltaTime: " << deltaTime
		<< ", FPS: " << (1.0f / deltaTime)
		<< "\n";
	*/

	/*if (GetKeyDown('A'))
	{
		std::cout << "KeyDown\n";
	}
	if (GetKey('A'))
	{
		std::cout << "Key\n";
	}
	if (GetKeyUp('A'))
	{
		std::cout << "KeyUp\n";
	}*/

	// 레벨 업데이트
	if (mainLevel != nullptr)
	{
		mainLevel->Tick(deltaTime);
	}

	//if (GetKeyDown(VK_ESCAPE))
	//{
	//	Quit();
	//}
}

void Engine::Render()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

	if (mainLevel != nullptr)
	{
		mainLevel->Render();
	}
}
