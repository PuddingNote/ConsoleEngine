#pragma once

#include "Core.h"
#include <Windows.h>

/*
* Todo: 2025년 7월 24일
* RTTI 적용
* Engine 싱글톤(Singleton) 구현
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

	// 키 입력 정보 관리 변수
	KeyState keyStates[255];// = { };

	// 메인 레벨
	Level* mainLevel = nullptr;
};