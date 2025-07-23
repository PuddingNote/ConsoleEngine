#include <iostream>
#include "TestActor.h"

void TestActor::Tick(float deltaTime)
{
	Actor::Tick(deltaTime);

	std::cout << "TestActor::Tick. FPS: " << (1.0f / deltaTime) << "\n";
}
