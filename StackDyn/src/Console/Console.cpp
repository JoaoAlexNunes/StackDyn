#include "Console.h"

Console::Console()
{
	Draw();
}

Console::~Console()
{
}
void Console::Draw()
{
	SetConsoleTitle(TEXT("3.3.0 - Build 30.0.100.9805"));
	std::cout << "Test Console writing" << std::endl;
}

