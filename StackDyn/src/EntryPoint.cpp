#include "GUI/GuiDraw.h"
#include "Console/Console.h"
#include <thread>

int main(void)
{
    Console console;
    GuiDraw gui;

    std::thread consoleThread([&]() {
        console.Init();
        });

    std::thread guiThread([&]() {
        gui.Init();
        });

    consoleThread.join();
    guiThread.join();
    
    return 0;
}