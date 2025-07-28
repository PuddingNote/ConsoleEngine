#include "Level.h"
#include "Actor/Actor.h"

Level::Level()
{

}

Level::~Level()
{
	// 메모리 해제
	for (Actor* actor : actors)
	{
		//// null 확인 후 액터 제거
		//if (actor)
		//{
		//	delete actor;
		//	actor = nullptr;
		//}

		SafeDelete(actor);
	}

	// std::vector 정리
	actors.clear();
}

void Level::AddActor(Actor* newActor)
{
	// 예외처리(중복 여부 확인) 필요함

	// 배열 맨 뒤에 새로운 항목 추가하는 함수
	actors.emplace_back(newActor);
	//actors.push_back(newActor);
}

void Level::BeginPlay()
{
	for (Actor* const actor : actors)
	{
		if (actor->HasBeganPlay())
		{
			continue;
		}

		actor->BeginPlay();
	}
}

void Level::Tick(float deltaTime)
{
	for (Actor* const actor : actors)
	{
		actor->Tick(deltaTime);
	}
}

void Level::Render()
{
	for (Actor* const actor : actors)
	{
		actor->Render();
	}
}