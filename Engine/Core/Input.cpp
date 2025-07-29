#include "Input.h"
#include <Windows.h>

// static 변수 정의
Input* Input::instance = nullptr;

Input::Input()
{
	// 싱글톤 실행을 위해 instance 변수 설정
	instance = this;
}

void Input::ProcessInput()
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

void Input::SavePreviousKeyStates()
{
	for (int i = 0; i < 255; ++i)
	{
		keyStates[i].previousKeyDown = keyStates[i].isKeyDown;
	}
}

bool Input::GetKey(int keyCode)
{
	return keyStates[keyCode].isKeyDown;
}

bool Input::GetKeyDown(int keyCode)
{
	return !keyStates[keyCode].previousKeyDown
		&& keyStates[keyCode].isKeyDown;
}

bool Input::GetKeyUp(int keyCode)
{
	return keyStates[keyCode].previousKeyDown
		&& !keyStates[keyCode].isKeyDown;
}

Input& Input::Get()
{
	return *instance;
}