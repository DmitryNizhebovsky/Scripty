// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include <fstream>
#include "Parser.h"
#include "Lexer.h"
#include "Functions.h"

void pause();

int main(int argc, char* argv[]) {
	std::ifstream source;
	source.open("D:\\Projects Visual Studio\\Calc\\Tests\\program.vsc");

	std::string input((std::istreambuf_iterator<char>(source)), std::istreambuf_iterator<char>());

	Lexer lexer(input);
    std::vector<Token> tokens;

    try {
        tokens = lexer.tokenize();
    }
    catch (std::exception &ex) {
        std::cout << ex.what() << std::endl;
        pause();
        return -1;
    }

	Scope globalScope;

	globalScope.defineFunction("sin", std::make_unique<SinFunction>());
	globalScope.defineFunction("cos", std::make_unique<CosFunction>());
	globalScope.defineFunction("sqrt", std::make_unique<SqrtFunction>());
	globalScope.defineFunction("print", std::make_unique<PrintFunction>());
	globalScope.defineFunction("println", std::make_unique<PrintLnFunction>());

	Parser parser(tokens);
    std::unique_ptr<IStatement> program = nullptr;

    try {
        program = parser.parse();
    }
    catch (LangException &ex) {
        std::cout << ex.what() << std::endl;
        pause();
        return -1;
    }

    try {
	    program->execute(globalScope);
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