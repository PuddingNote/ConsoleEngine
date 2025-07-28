#include "SokobanLevel.h"
#include "Math/Vector2.h"

#include "Actor/Player.h"
#include "Actor/Wall.h"
#include "Actor/Ground.h"
#include "Actor/Box.h"
#include "Actor/Target.h"

#include <iostream>

SokobanLevel::SokobanLevel()
{
	ReadMapFile("Map.txt");
}

void SokobanLevel::ReadMapFile(const char* filename)
{
	char filepath[256] = {};
	sprintf_s(filepath, 256, "../Assets/%s", filename);

	FILE* file = nullptr;
	fopen_s(&file, filepath, "rb");

	if (file == nullptr)
	{
		std::cout << "맵 파일 읽기 실패." << filename << "\n";
		__debugbreak();
		return;
	}

	// 파싱 (해석)
	fseek(file, 0, SEEK_END);
	size_t fileSize = ftell(file);
	rewind(file);

	// 확인한 파일 크기를 활용해 버퍼 할당
	char* buffer = new char[fileSize + 1];
	//buffer[fileSize] = '\0';
	memset(buffer, 0, fileSize + 1);
	size_t readSize = fread(buffer, sizeof(char), fileSize, file);

	if (fileSize != readSize)
	{
		std::cout << "fileSize is not matched with readSize.\n";
	}

	int index = 0;				// 배열 순회를 위한 인덱스 변수
	int size = (int)readSize;	// 문자열 길이 값
	Vector2 position;			// x, y 좌표

	while (index < size)
	{
		char mapCharacter = buffer[index++];	// 맵 문자 확인

		// 개행 문자 처리
		if (mapCharacter == '\n')
		{
			++position.y;
			position.x = 0;

			// Todo: 테스트용도. 나중에 삭제
			std::cout << '\n';
			continue;
		}

		switch (mapCharacter)
		{
		case '#':
			AddActor(new Wall(position));
			//std::cout << '#';
			break;
		case '.':
			AddActor(new Ground(position));
			//std::cout << '.';
			break;
		case 'p':
			AddActor(new Player(position));
			//std::cout << 'p';
			break;
		case 'b':
			AddActor(new Box(position));
			//std::cout << 'b';
			break;
		case 't':
			AddActor(new Target(position));
			//std::cout << 't';
			break;
		}

		++position.x;
	}

	// 버퍼 해제
	delete[] buffer;

	fclose(file);
}