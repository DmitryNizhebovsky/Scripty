// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "Program.h"

Program::Program(const std::string& fileName): sourceFile(fileName) {}

void Program::Initialization() noexcept {
    globalScope.defineFunction("sin", std::make_unique<SinFunction>());
    globalScope.defineFunction("cos", std::make_unique<CosFunction>());
    globalScope.defineFunction("sqrt", std::make_unique<SqrtFunction>());
    globalScope.defineFunction("print", std::make_unique<PrintFunction>());
    globalScope.defineFunction("println", std::make_unique<PrintLnFunction>());
}

void Program::ReadProgram() {
    std::vector<Token> tokens = lexer.tokenize(sourceFile);

    program = parser.parse(std::move(tokens));
}

void Program::Run() {
    ReadProgram();
    Initialization();

    program->execute(globalScope);
}