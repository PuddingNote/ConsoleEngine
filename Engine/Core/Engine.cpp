#include <iostream>
#include "Engine.h"
#include "Level/Level.h"
#include <Windows.h>

// ���� ���� ȣ��ȭ
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
		ProcessInput();

		// ����������
		if (deltaTime >= oneFrameTime) 
		{
			BeginPlay();
			Tick(deltaTime);
			Render();

			// �ð� ������Ʈ
			previousTime = currentTime;
		
			// ���� �������� �Է��� ���
			for (int i = 0; i < 255; ++i)
			{
				keyStates[i].previousKeyDown = keyStates[i].isKeyDown;
			}
		}
	}

	// ���� (���� ����� ����)
	


	// ��� �ؽ�Ʈ ���� ����
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
	// Ű �Է� Ȯ��
	for (int i = 0; i < 255; ++i)
	{
		keyStates[i].isKeyDown = GetAsyncKeyState(i) & 0x8000;
	}

	// ESCŰ ���� Ȯ��
	// 0x8000 : ������ ���� ���� ���� ȣ�� �������� �����ִ� ����
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
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

	if (mainLevel != nullptr)
	{
		mainLevel->Render();
	}
}
