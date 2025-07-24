#pragma once

#include "Core.h"
#include "Math/Vector2.h"
#include "RTTI.h"

// 물체가 뭘 해야할지 정의
// 위치 점령
// 콘솔 창에 그리기 (How? What?)
// 엔진의 이벤트 함수 호출 (BeginPlay, Tick, Draw)
class Engine_API Actor : public RTTI
{
	RTTI_DECLARATIONS(Actor, RTTI)

public:
	Actor();
	virtual ~Actor();

	// 이벤트 함수
	virtual void BeginPlay();			// 초기화 목적으로 처음에 1번만 호출
	virtual void Tick(float deltaTime);	// 프레임 마다 호출
	virtual void Render();				// 그리기 함수
	inline bool HasBeganPlay() const { return hasBeganPlay; }

private:
	Vector2 position;
	char image = ' ';
	bool hasBeganPlay = false;
};