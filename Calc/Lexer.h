#pragma once

#include "Token.h"
#include <vector>
#include <map>

class Lexer {
private:
	size_t position;
	size_t length;
	TokenPosition currentPos;
	std::string input;
	std::vector<Token> tokens;
	std::map<std::string, TokenType> operators;

private:
	void addToken(const TokenType type, const TokenPosition& pos, const std::string& value = "");
	void tokenizeNumber();
	void tokenizeWord();
	void tokenizeString();
	void tokenizeOperator();
	void skipComments();
    void skipSinglelineComment();
	void skipMultilineComment();

	bool isDigit(const char let) const;
	bool isLetter(const char let) const;
	bool isLetterOrDigit(const char let) const;
	bool isOperator(const char let) const;
    bool isComment(const char let) const;
    bool isString(const char let) const;

	char peek(size_t relativePos = 0) const;
	char next();

public:
	Lexer(const std::string& input);
	std::vector<Token>& tokenize();
};