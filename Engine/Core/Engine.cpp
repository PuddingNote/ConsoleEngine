#include <iostream>
#include "Engine.h"
#include "Level/Level.h"
#include <Windows.h>
#include "Utils/Utils.h"

// ���� ���� ȣ��ȭ
Engine* Engine::instance = nullptr;

BOOL WINAPI ConsoleMessageProcedure(DWORD CtrlType)
{
	switch (CtrlType)
	{
	case CTRL_CLOSE_EVENT:
		// Engine�� �޸� ����
		// Todo: Engine�� �޸� ���� �Լ� �߰� �� ȣ���ؾ� ��
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
	
	// �ܼ� â �̺�Ʈ ���
	SetConsoleCtrlHandler(ConsoleMessageProcedure, TRUE);
}

Engine::~Engine()
{
	CleanUp();
}

void Engine::Run()
{
	// �и� ������ ������ �ð��� �˷���
	//float currentTime = timeGetTime();
	LARGE_INTEGER currentTime;
	LARGE_INTEGER previousTime;
	QueryPerformanceCounter(&currentTime);
	previousTime = currentTime;

	// �ϵ���� �ð��� ���е�(���ļ�) �������� : ���߿� �ʷ� ��ȯ�ϱ� ����
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	float targetFrameRate = 60.0f;					// Ÿ�� ������
	float oneFrameTime = 1.0f / targetFrameRate;	// Ÿ�� �� ������ �ð�

	while (true)
	{
		if (isQuit)
		{
			break;
		}

		// ������ �ð� ��� : (���� �ð� - ���� �ð�) / ���ļ� = �ʴ���
		QueryPerformanceCounter(&currentTime);
		float deltaTime = (currentTime.QuadPart - previousTime.QuadPart) / (float)frequency.QuadPart;

		// �Է��� �ִ��� ����
		input.ProcessInput();

		// ����������
		if (deltaTime >= oneFrameTime) 
		{
			BeginPlay();
			Tick(deltaTime);
			Render();

			// �ð� ������Ʈ
			previousTime = currentTime;
		
			// ���� �������� �Է��� ���
			input.SavePreviousKeyStates();
		}
	}

	// ���� (���� ����� ����)
	


	// ��� �ؽ�Ʈ ���� ������� ����
	Utils::SetConsoleTextColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void Engine::Quit()
{
	isQuit = true;
}

void Engine::CleanUp()
{
	// ���� ����
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

	// ���� ������Ʈ
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
