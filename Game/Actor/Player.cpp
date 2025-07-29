#include "Player.h"
#include "Engine.h"
#include "Game/Game.h"
#include "Input.h"
#include "Level/Level.h"
#include "Interface/ICanPlayerMove.h"

#include <iostream>

Player::Player(const Vector2& position) : Actor('P', Color::Red, position)
{
	SetSortingOrder(3);
}

void Player::BeginPlay()
{
	Actor::BeginPlay();	// super::BeginPlay();

	// 인터페이스 얻어오기
	if (GetOwner())
	{
		canPlayerMoveInterface = dynamic_cast<ICanPlayerMove*>(GetOwner());

		if (!canPlayerMoveInterface)
		{
			std::cout << "Can not cast owner level to ICanPlayerMove.\n";
		}
	}
}

void Player::Tick(float deltaTime)
{
	Actor::Tick(deltaTime);

	// ESC 종료
	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		//Engine::Get().Quit();
		//QuitGame();

		Game::Get().ToggleMenu();
		return;
	}

	// 입력처리 (이동 가능 여부 판단 후 이동)
	if (Input::Get().GetKeyDown(VK_LEFT))
	{
		bool canMove = canPlayerMoveInterface->CanPlayerMove(Position(), Vector2(Position().x - 1, Position().y));
		if (canMove)
		{
			Vector2 position = Position();
			position.x -= 1;
			SetPosition(position);
		}
	}
	if (Input::Get().GetKeyDown(VK_RIGHT))
	{
		bool canMove = canPlayerMoveInterface->CanPlayerMove(Position(), Vector2(Position().x + 1, Position().y));
		if (canMove)
		{
			Vector2 position = Position();
			position.x += 1;
			SetPosition(position);
		}
	}
	if (Input::Get().GetKeyDown(VK_UP))
	{
		bool canMove = canPlayerMoveInterface->CanPlayerMove(Position(), Vector2(Position().x, Position().y - 1));
		if (canMove)
		{
			Vector2 position = Position();
			position.y -= 1;
			SetPosition(position);
		}
	}
	if (Input::Get().GetKeyDown(VK_DOWN))
	{
		bool canMove = canPlayerMoveInterface->CanPlayerMove(Position(), Vector2(Position().x, Position().y + 1));
		if (canMove)
		{
			Vector2 position = Position();
			position.y += 1;
			SetPosition(position);
		}
	}

}