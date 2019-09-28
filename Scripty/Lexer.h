#pragma once

#include "Token.h"
#include <fstream>
#include <vector>
#include <map>

class Lexer {
private:
	size_t position;
	size_t sourceCodeLength;
	TokenPosition currentPos;
	std::string sourceCode;
	std::vector<Token> tokens;

private:
	void addToken(const TokenType type, const TokenPosition& pos, const std::string& value = "");
	void tokenizeNumber();
	void tokenizeWord();
	void tokenizeString();
	void tokenizeOperator();
	void skipComments();
    void skipSinglelineComment();
	void skipMultilineComment();

	bool isLetterOrDigit(const char let) const;
	bool isOperator(const char let) const;
    bool isComment(const char let) const;
    bool isLetter(const char let) const;
    bool isString(const char let) const;
    bool isDigit(const char let) const;

    void readSourceFile(const std::string& fileName);
	char peek(size_t relativePos = 0) const;
	char next();

public:
	Lexer();
	std::vector<Token>&& tokenize(const std::string& fileName);
};