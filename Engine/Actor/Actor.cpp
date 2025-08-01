#include <Windows.h>
#include <iostream>

#include "Actor.h"
#include "Utils/Utils.h"
#include "Engine.h"

Actor::Actor(const char image, Color color, const Vector2& position) : image(image), color(color), position(position)
{

}

Actor::~Actor()
{

}

void Actor::BeginPlay()
{
	hasBeganPlay = true;
}

void Actor::Tick(float deltaTime)
{

}

// 그리기 함수
void Actor::Render()
{
	// 콘솔 출력을 제어하는 핸들 얻어오기
	static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	// 커서 위치 값 생성
	COORD coord;
	coord.X = (short)position.x;
	coord.Y = (short)position.y;

	// 커서 이동
	//SetConsoleCursorPosition(handle, coord);
	Utils::SetConsolePosition(coord);

	// 색상 설정
	//SetConsoleTextAttribute(handle, (WORD)color);
	Utils::SetConsoleTextColor(static_cast<WORD>(color));

	// 그리기
	std::cout << image;
}

void Actor::SetPosition(const Vector2& newPosition)
{
	// 콘솔 출력을 제어하는 핸들 얻어오기
	//static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	// 커서 위치 값 생성
	COORD coord;
	coord.X = (short)position.x;
	coord.Y = (short)position.y;
	
	// 커서 이동
	//SetConsoleCursorPosition(handle, coord);
	Utils::SetConsolePosition(coord);
	
	std::cout << ' ';

	position = newPosition;
}

Vector2 Actor::Position() const
{
	return position;
}

void Actor::SetSortingOrder(unsigned int sortingOrder)
{
	this->sortingOrder = sortingOrder;
}

void Actor::SetOwner(Level* newOwner)
{
	owner = newOwner;
}

Level* Actor::GetOwner()
{
	return owner;
}

void Actor::QuitGame()
{
	Engine::Get().Quit();
}