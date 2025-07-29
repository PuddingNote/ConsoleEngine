#include <iostream>
#include "Engine.h"
#include "Level/Level.h"
#include <Windows.h>
#include "Utils/Utils.h"

// 정적 변수 호기화
Engine* Engine::instance = nullptr;

BOOL WINAPI ConsoleMessageProcedure(DWORD CtrlType)
{
	switch (CtrlType)
	{
	case CTRL_CLOSE_EVENT:
		// Engine의 메모리 해제
		// Todo: Engine에 메모리 해제 함수 추가 후 호출해야 함
		Engine::Get().CleanUp();
		return false;
	}
	return false;
}

Engine::Engine()
{
	instance = this;

	CONSOLE_CURSOR_INFO info;
	info.bVisible = false;
	info.dwSize = 1;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	
	// 콘솔 창 이벤트 등록
	SetConsoleCtrlHandler(ConsoleMessageProcedure, TRUE);
}

Engine::~Engine()
{
	CleanUp();
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
		input.ProcessInput();

		// 고정프레임
		if (deltaTime >= oneFrameTime) 
		{
			BeginPlay();
			Tick(deltaTime);
			Render();

			// 시간 업데이트
			previousTime = currentTime;
		
			// 현재 프레임의 입력을 기록
			input.SavePreviousKeyStates();
		}
	}

	// 정리 (게임 종료시 실행)
	


	// 모든 텍스트 색상 원래대로 변경
	Utils::SetConsoleTextColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void Engine::Quit()
{
	isQuit = true;
}

void Engine::CleanUp()
{
	// 레벨 삭제
	SafeDelete(mainLevel);
	
	/*if (mainLevel != nullptr)
	{
		delete mainLevel;
		mainLevel = nullptr;
	}*/
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
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	Utils::SetConsoleTextColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

	if (mainLevel != nullptr)
	{
		mainLevel->Render();
	}
}
