#include "DemoLevel.h"
#include "TestActor.h"
#include <iostream>

DemoLevel::DemoLevel()
{
	AddActor(new TestActor());

	// 맵 파일 읽기
	FILE* file = nullptr;
	fopen_s(&file, "../Assets/Map.txt", "rb");

	// 예외처리
	if (file == nullptr)
	{
		std::cout << "Failed to open Map.txt file.\n";
		__debugbreak();
		return;
	}

	// 파일 크기 확인
	fseek(file, 0, SEEK_END);		// 커서를 파일 끝으로 이동
	size_t fileSize = ftell(file);	// 커서의 위치 반환
	fseek(file, 0, SEEK_SET);		// 커서를 파일 처음으로 이동

	// 데이터 저장을 위한 버퍼 할당
	//char* buffer = new char[fileSize + 1];
	char buffer[256] = {};

	// 파일 종료시점까지 반복
	while (!feof(file))
	{
		// 한줄씩 읽기
		fgets(buffer, 256, file);

		// 한줄 문자열의 길이 구하기
		int lineLength = (int)strlen(buffer);

		// 파싱 (해석)
		for (int i = 0; i < lineLength; ++i)
		{
			char mapCharacter = buffer[i];

			switch (mapCharacter)
			{
			case '#':
				std::cout << '#';
				break;
			case '.':
				std::cout << '.';
				break;
			case 'p':
				std::cout << 'p';
				break;
			case 'b':
				std::cout << 'b';
				break;
			case 't':
				std::cout << 't';
				break;
			}
		}

		std::cout << "\n";
	}

	fclose(file);

}
