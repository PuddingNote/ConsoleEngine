#pragma once

#include "Core.h"
#include "Input.h"
#include <Windows.h>

class Level;
class Engine_API Engine
{
public:
	Engine();
	~Engine();

	void Run();		// 
	void Quit();	// 종료 함수
	void CleanUp();	// 메모리 해제 함수

	void AddLevel(Level* newLevel);

	static Engine& Get();

private:
	void BeginPlay();
	void Tick(float deltaTime = 0.0f);	// Update()
	void Render();

private:
	bool isQuit = false;		// 엔진 종료 플래그

	Level* mainLevel = nullptr;	// 메인 레벨

	Input input;				// 입력 관리자

	static Engine* instance;	// 싱글톤 변수
};