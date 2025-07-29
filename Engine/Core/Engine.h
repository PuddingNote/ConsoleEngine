#pragma once

#include "Core.h"
#include "Input.h"
#include <Windows.h>

class Level;
class Engine_API Engine
{
public:
	Engine();
	virtual ~Engine();

	void Run();				// ���� ���� �Լ�
	void Quit();			// ���� �Լ�
	virtual void CleanUp();	// �޸� ���� �Լ�

	void AddLevel(Level* newLevel);

	static Engine& Get();

private:
	void BeginPlay();
	void Tick(float deltaTime = 0.0f);	// Update()
	void Render();

protected:
	bool isQuit = false;		// ���� ���� �÷���

	Level* mainLevel = nullptr;	// ���� ����

	Input input;				// �Է� ������

	static Engine* instance;	// �̱��� ����
};