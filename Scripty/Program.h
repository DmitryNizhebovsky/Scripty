#pragma once

#include <fstream>
#include "Parser.h"
#include "Lexer.h"
#include "Functions.h"

class Program: public NonCopyable {
private:
    Lexer  lexer;
    Parser parser;
    Scope  globalScope;
    std::unique_ptr<IStatement> program;
    std::string sourceFile;

private:
    void Initialization() noexcept;
    void ReadProgram();

public: 
    Program(const std::string& fileName);
    void Run();
    ~Program() = default;
};
