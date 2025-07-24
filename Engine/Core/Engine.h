#pragma once

#include "Core.h"
#include <Windows.h>

/*
* Todo: 2025�� 7�� 24��
* RTTI ����
* Engine �̱���(Singleton) ����
* 
*/

class Level;
class Engine_API Engine
{
	struct KeyState
	{
		bool isKeyDown = false;
		bool previousKeyDown = false;
	};

public:
	Engine();
	~Engine();

	void Run();
	void Quit();

	bool GetKey(int keyCode);
	bool GetKeyDown(int keyCode);
	bool GetKeyUp(int keyCode);
	
	void AddLevel(Level* newLevel);

private:
	void ProcessInput();
	void BeginPlay();
	void Tick(float deltaTime = 0.0f);	// Update()
	void Render();

private:
	bool isQuit = false;

	// Ű �Է� ���� ���� ����
	KeyState keyStates[255];// = { };

	// ���� ����
	Level* mainLevel = nullptr;
};