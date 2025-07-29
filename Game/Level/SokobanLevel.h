#pragma once

#include "Level/Level.h"
#include "Interface/ICanPlayerMove.h"

class SokobanLevel : public Level, public ICanPlayerMove
{
	RTTI_DECLARATIONS(SokobanLevel, Level)
	
public:
	SokobanLevel();

	virtual void Render() override;

	// ICanPlayerMove��(��) ���� ��ӵ�
	virtual bool CanPlayerMove(const Vector2& playerPosition, const Vector2& targetPosition) override;

private:
	void ReadMapFile(const char* filename);	// �� ������ �о ���� ��ü �����ϴ� �Լ�
	bool CheckGameClear();		// ���� Ŭ���� Ȯ�� �Լ�

private:
	int targetScore = 0;		// ���� Ŭ��� ���� ����

	bool isGameClear = false;	// ���� Ŭ���� ���� Ȯ�� ����
};