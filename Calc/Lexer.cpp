// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "Lexer.h"

Lexer::Lexer() :
    sourceCodeLength(0),
    position(0),
    currentPos{ 1, 1 } {}				   
					   
void Lexer::addToken(const TokenType type, const TokenPosition& pos, const std::string& value) {
	tokens.emplace_back(Token(type, value, pos));
}		

void Lexer::readSourceFile(const std::string& fileName) {
    std::ifstream sourceFile(fileName, std::fstream::in);

    if (!sourceFile.is_open()) {
        throw std::runtime_error("Unable to open source file");
    }

    sourceFile.seekg(0, sourceFile.end);
    sourceCodeLength = sourceFile.tellg();
    sourceFile.seekg(0, sourceFile.beg);

    sourceCode.reserve(sourceCodeLength);
    sourceCode.resize(sourceCodeLength);

    sourceFile.read(&sourceCode[0], sourceCodeLength);

    sourceFile.close();
}
					   
char Lexer::peek(size_t relativePos) const{
	size_t pos = position + relativePos;
					   
	if (pos >= sourceCodeLength) {
		return '\0';   
	}				   

	return sourceCode[pos];
}					   

char Lexer::next() {
	if (sourceCode[position] == '\r' || sourceCode[position] == '\n') {
		currentPos.row++;
		currentPos.column = 0;
	}

	currentPos.column++;
	position++;
	return peek();
}

void Lexer::tokenizeNumber() {
	TokenPosition tokenPos = currentPos;
	char current = peek();
	std::string buffer = "";

	while (true) {
		if (isDigit(current)) {
			buffer += current;
		} else if (current == '.'){
			if (buffer.find('.') == std::string::npos) {
				buffer += current;
			} else {
				throw std::runtime_error("NumberFormatException");
			}
		} else {
			break;
		}

		current = next();
	}

	addToken(TokenType::NUMBER, tokenPos, buffer);
}

void Lexer::tokenizeWord() {
	TokenPosition tokenPos = currentPos;
	char current = peek();
	std::string buffer = "";

	while (true) {
		if (!isLetterOrDigit(current)) {
			break;
		}

		buffer += current;
		current = next();
	}

    if (Token::isKeyword(buffer)) {
        addToken(Token::keywords.at(buffer), tokenPos, buffer);
    } else {
        addToken(TokenType::WORD, tokenPos, buffer);
    }
}

void Lexer::tokenizeString() {
	TokenPosition tokenPos = currentPos;
    char openingQuote      = peek();
	char current           = next();
	std::string buffer     = "";

	while (true) {
		if (current == '\\') {
			current = next();

            if (current == openingQuote) { current = next(); buffer += openingQuote; continue; }

			switch (current)
			{
				case 'r':  current = next(); buffer += '\r'; continue;
				case 'n':  current = next(); buffer += '\n'; continue;
				case 't':  current = next(); buffer += '\t'; continue;
				case 'v':  current = next(); buffer += '\v'; continue;
				case '\\': current = next(); buffer += '\\'; continue;
			}
		}

        if (current == openingQuote) {
			break;
		}

		buffer += current;
		current = next();
	}

	next();
	addToken(TokenType::STRING, tokenPos, buffer);
}

void Lexer::tokenizeOperator() {
	TokenPosition tokenPos = currentPos;
	char current = peek();
	std::string buffer = "";

	while (true) {
        if (!Token::isOperator(buffer + current) && buffer.size() != 0) {
            addToken(Token::operators.at(buffer), tokenPos, buffer);
			return;
		}

		buffer += current;
		current = next();
	}
}

void Lexer::skipComments() {
    char current = peek();

    if (current == '#') {
        skipSinglelineComment();
    } else if (current == '/' && peek(1) == '*') {
    	skipMultilineComment();
    }
}

void Lexer::skipSinglelineComment() {
	char current = peek();

	while (current != '\n' && current != '\r' && current != '\0') {
		current = next();
	}
}

void Lexer::skipMultilineComment() {
	next();
	next();
	char current = peek();

	while (true) {
		if (current == '*' && peek(1) == '/') {
			break;
		}

		if (current == '\0') {
			throw std::runtime_error("Closing comment tag was not found");
		}

		current = next();
	}

	next();
	next();
}

bool Lexer::isOperator(const char let) const {
    return Token::isOperator(std::string(1, let));
}

bool Lexer::isDigit(const char let) const {
	return let >= '0' && let <= '9';
}

bool Lexer::isLetter(const char let) const {
	return (let >= 'a' && let <= 'z') || (let >= 'A' && let <= 'Z') || let == '_';
}

bool Lexer::isLetterOrDigit(const char let) const {
	return isLetter(let) || isDigit(let);
}

bool Lexer::isComment(const char let) const {
    return (let == '#') || (let == '/' && peek(1) == '*');
}

bool Lexer::isString(const char let) const {
    return let == '"' || let == '\'';
}

std::vector<Token>&& Lexer::tokenize(const std::string& fileName) {
    readSourceFile(fileName);

	while (position < sourceCodeLength) {
		char current = peek();

        if (isComment(current)) {
            skipComments();
        }
		else if (isDigit(current)) {
			tokenizeNumber();
		} 
        else if (isLetter(current)) {
			tokenizeWord();
		} 
        else if (isOperator(current)) {
			tokenizeOperator();
		} 
        else if (isString(current)) {
			tokenizeString();
		} 
        else {
			next();
		}
	}

	return std::move(tokens);
}