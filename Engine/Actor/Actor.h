#pragma once

#include "Core.h"
#include "Math/Vector2.h"
#include "RTTI.h"

// ��ü�� �� �ؾ����� ����
// ��ġ ����
// �ܼ� â�� �׸��� (How? What?)
// ������ �̺�Ʈ �Լ� ȣ�� (BeginPlay, Tick, Draw)
class Engine_API Actor : public RTTI
{
	RTTI_DECLARATIONS(Actor, RTTI)

public:
	Actor();
	virtual ~Actor();

	// �̺�Ʈ �Լ�
	virtual void BeginPlay();			// �ʱ�ȭ �������� ó���� 1���� ȣ��
	virtual void Tick(float deltaTime);	// ������ ���� ȣ��
	virtual void Render();				// �׸��� �Լ�
	inline bool HasBeganPlay() const { return hasBeganPlay; }

private:
	Vector2 position;
	char image = ' ';
	bool hasBeganPlay = false;
};