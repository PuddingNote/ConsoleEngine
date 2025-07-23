#pragma once

#include "Core.h"
#include <Windows.h>

/*
* Todo: 2025년 7월 23일 작업할 것.
  - 키 입력 관리 (KeyState 배열) - 완료
  - 입력 확인 함수 (GetKey, GetKeyDown, GetKeyUp) - 완료

  - Entity 추가 (Actor) - 
  - 이벤트 함수 추가 (BeginPlay, Tick, Render) - 완료

  - Level 추가 (가상 공간에 배치된 물체(Actor) 관리 객체) - 
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