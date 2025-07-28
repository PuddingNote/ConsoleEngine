#include "DemoLevel.h"
#include "TestActor.h"
#include <iostream>

DemoLevel::DemoLevel()
{
	AddActor(new TestActor());

	// �� ���� �б�
	FILE* file = nullptr;
	fopen_s(&file, "../Assets/Map.txt", "rb");

	// ����ó��
	if (file == nullptr)
	{
		std::cout << "Failed to open Map.txt file.\n";
		__debugbreak();
		return;
	}

	// ���� ũ�� Ȯ��
	fseek(file, 0, SEEK_END);		// Ŀ���� ���� ������ �̵�
	size_t fileSize = ftell(file);	// Ŀ���� ��ġ ��ȯ
	fseek(file, 0, SEEK_SET);		// Ŀ���� ���� ó������ �̵�

	// ������ ������ ���� ���� �Ҵ�
	//char* buffer = new char[fileSize + 1];
	char buffer[256] = {};

	// ���� ����������� �ݺ�
	while (!feof(file))
	{
		// ���پ� �б�
		fgets(buffer, 256, file);

		// ���� ���ڿ��� ���� ���ϱ�
		int lineLength = (int)strlen(buffer);

		// �Ľ� (�ؼ�)
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
