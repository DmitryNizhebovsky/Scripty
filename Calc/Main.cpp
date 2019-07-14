// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include "Program.h"

void pause();

int main(int argc, char* argv[]) {

    try {
        Program program("D:\\Projects Visual Studio\\Calc\\Tests\\program.vsc");
        program.Run();
    }
    catch (std::exception &ex) {
        std::cout << ex.what() << std::endl;
        pause();
        return -1;
    }

    pause();
    return 0;
}

void pause() {
#ifdef _DEBUG
    getchar();
#endif
}