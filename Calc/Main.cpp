// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include "Program.h"
#include "CLI/CLI.hpp"

void pause();

int main(int argc, char* argv[]) {
    CLI::App app;

    std::string sourceFile;
    app.add_option("-f,--file", sourceFile, "File name")->check(CLI::ExistingFile);

    CLI11_PARSE(app, argc, argv);

    //"D:\\Projects Visual Studio\\Calc\\Tests\\program.vsc"

    try {
        Program program(sourceFile);
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