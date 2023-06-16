#include "GUI/GuiDraw.h"
#include "Console/Console.h"
#include <thread>

int main(void)
{
    Console console;
    //GuiDraw gui;

    std::thread consoleThread([&]() {
        console.Init();
        });

     

    consoleThread.join();
    //guiThread.join();
    
    return 0;
}