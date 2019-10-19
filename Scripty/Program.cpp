// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "Program.h"
#include "IFunction.h"
#include "Functions.h"
#include <vector>
#include <memory>

Program::Program(const std::string& fileName): sourceFile(fileName) {}

void Program::Initialization() noexcept {
    std::vector<std::unique_ptr<IFunction>> functions;

    functions.emplace_back(std::make_unique<SinFunction>());
    functions.emplace_back(std::make_unique<CosFunction>());
    functions.emplace_back(std::make_unique<SqrtFunction>());
    functions.emplace_back(std::make_unique<InputFunction>());
    functions.emplace_back(std::make_unique<PrintFunction>());
    functions.emplace_back(std::make_unique<PrintLnFunction>());

    for (auto& func : functions) {
        globalScope.defineFunction(func->getName(), std::move(func));
    }
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