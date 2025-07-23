#pragma once

#include "Core.h"
#include <Windows.h>

/*
* Todo: 2025�� 7�� 23�� �۾��� ��.
  - Ű �Է� ���� (KeyState �迭) - �Ϸ�
  - �Է� Ȯ�� �Լ� (GetKey, GetKeyDown, GetKeyUp) - �Ϸ�

  - Entity �߰� (Actor) - 
  - �̺�Ʈ �Լ� �߰� (BeginPlay, Tick, Render) - �Ϸ�

  - Level �߰� (���� ������ ��ġ�� ��ü(Actor) ���� ��ü) - 
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