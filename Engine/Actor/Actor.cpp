#include "Actor.h"
#include <Windows.h>
#include <iostream>

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

// �׸��� �Լ�
void Actor::Render()
{
	// �ܼ� ����� �����ϴ� �ڵ� ������
	static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	// Ŀ�� ��ġ �� ����
	COORD coord;
	coord.X = (short)position.x;
	coord.Y = (short)position.y;

	// Ŀ�� �̵�
	SetConsoleCursorPosition(handle, coord);

	// ���� ����
	SetConsoleTextAttribute(handle, (WORD)color);

	// �׸���
	std::cout << image;
}

void Actor::SetPosition(const Vector2& newPosition)
{
	// �ܼ� ����� �����ϴ� �ڵ� ������
	static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	// Ŀ�� ��ġ �� ����
	COORD coord;
	coord.X = (short)position.x;
	coord.Y = (short)position.y;
	SetConsoleCursorPosition(handle, coord);

	// Ŀ�� �̵�
	SetConsoleTextAttribute(handle, (WORD)color);
	
	std::cout << ' ';

	position = newPosition;
}

Vector2 Actor::Position() const
{
	return position;
}
