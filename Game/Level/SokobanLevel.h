#pragma once

#include "Level/Level.h"
#include "Interface/ICanPlayerMove.h"

class SokobanLevel : public Level, public ICanPlayerMove
{
	RTTI_DECLARATIONS(SokobanLevel, Level)
	
public:
	SokobanLevel();

	virtual void Render() override;

	// ICanPlayerMove을(를) 통해 상속됨
	virtual bool CanPlayerMove(const Vector2& playerPosition, const Vector2& targetPosition) override;

private:
	void ReadMapFile(const char* filename);	// 맵 파일을 읽어서 게임 객체 생성하는 함수
	bool CheckGameClear();		// 게임 클리어 확인 함수

private:
	int targetScore = 0;		// 게임 클리어를 위한 점수

	bool isGameClear = false;	// 게임 클리어 여부 확인 변수
};