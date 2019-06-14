#include <iostream>
#include <fstream>
#include "Parser.h"
#include "Lexer.h"
#include "Functions.h"

int main() {
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
        getchar();
        return -1;
    }

	//for (auto it = tokens.begin(); it != tokens.end(); ++it) {
	//	std::cout << (*it).toString() << std::endl;
	//}

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
        getchar();
        return -1;
    }

    try {
	    program->execute(globalScope);
    }
    catch (std::exception &ex) {
        std::cout << ex.what() << std::endl;
        getchar();
        return -1;
    }

    getchar();
	return 0;
}