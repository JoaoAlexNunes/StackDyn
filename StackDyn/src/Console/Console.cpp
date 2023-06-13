#include "Console.h"

Console::Console()
{
	Draw();
    CreateArrivalStack();
}

Console::~Console()
{
}
void Console::Draw()
{
	SetConsoleTitle(TEXT("3.3.0 - Build 30.0.100.9805"));
	std::cout << "Test Console writing" << std::endl;
}

void Console::CreateArrivalStack()
{
	Stack* arrivalStack = new Stack(1, 4);
    std::cout << "Arrival Stack ID: " << arrivalStack->StackID << std::endl;
    std::cout << "Arrival Stack Weight: " << arrivalStack->Weigth << std::endl;

    // Accessing and modifying values in the arrival stack
    for (int i = 0; i < arrivalStack->Weigth; i++) {
        arrivalStack->Blocklist[i] = i * 2;
    }

    std::cout << "Arrival Stack Values: ";
    for (int i = 0; i < arrivalStack->Weigth; i++) {
        std::cout << arrivalStack->Blocklist[i] << " ";
    }

}

