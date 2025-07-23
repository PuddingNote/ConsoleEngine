#pragma once

#include "Core.h"
#include <vector>

class Actor;
class Engine_API Level
{
public:
	Level();
	virtual ~Level();
	
	// Level�� Actor�� �߰��� �� ���
	void AddActor(Actor* newActor);

	// ���� �̺�Ʈ �Լ�
	virtual void BeginPlay();
	virtual void Tick(float deltaTime);
	virtual void Render();

private:
	// ������ ��ġ�� ��� Actor�� �����ϴ� �迭
	std::vector<Actor*> actors;
};