#include "Lexer.h"

Lexer::Lexer(const std::string& input) :
    input(input),
    length(input.size()),
    position(0),
    currentPos{ 1, 1 },
    operators{
        { "+",  TokenType::PLUS },
        { "-",  TokenType::MINUS },
        { "*",  TokenType::MULTIPLY },
        { "/",  TokenType::DIVISION },
        { "%",  TokenType::MOD },
        { "//", TokenType::DIV },
        { "(",  TokenType::OPEN_BRACKET },
        { ")",  TokenType::CLOSE_BRACKET },
        { "[",  TokenType::OPEN_SQUARE_BRACKET },
        { "]",  TokenType::CLOSE_SQUARE_BRACKET },
        { "{",  TokenType::OPEN_BRACES },
        { "}",  TokenType::CLOSE_BRACES },
        { "=",  TokenType::ASSIGN },
        { ">",  TokenType::GREATER_THAN },
        { "<",  TokenType::LESS_THAN },
        { "!",  TokenType::LOGICAL_NOT },
        { ".",  TokenType::DOT },
        { ",",  TokenType::COMMA },
        { ":",  TokenType::COLON },
        { ";",  TokenType::SEMICOLON },
        { "+=", TokenType::PLUS_ASSIGN },
        { "-=", TokenType::MINUS_ASSIGN },
        { "*=", TokenType::MULTIPLY_ASSIGN },
        { "/=", TokenType::DIVISION_ASSIGN },
        { "%=", TokenType::MOD_ASSIGN },
        { "//=",TokenType::DIV_ASSIGN },
        { "==", TokenType::EQUALS },
        { "!=", TokenType::NOT_EQUALS },
        { ">=", TokenType::GREATER_OR_EQUALS },
        { "<=", TokenType::LESS_OR_EQUALS },
        { "&&", TokenType::LOGICAL_AND },
        { "||", TokenType::LOGICAL_OR }
    } {}				   
					   
void Lexer::addToken(const TokenType type, const TokenPosition& pos, const std::string& value) {
	tokens.emplace_back(Token(type, value, pos));
}					   
					   
char Lexer::peek(size_t relativePos) const{
	size_t pos = position + relativePos;
					   
	if (pos >= length) {
		return '\0';   
	}				   
					   
	return input[pos]; 
}					   

char Lexer::next() {
	if (input[position] == '\r' || input[position] == '\n') {
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

	if (buffer == "if") {
		addToken(TokenType::IF, tokenPos, buffer);
	}
	else if (buffer == "else") {
		addToken(TokenType::ELSE, tokenPos, buffer);
	}
	else if (buffer == "true") {
		addToken(TokenType::TRUE, tokenPos, buffer);
	}
	else if (buffer == "false") {
		addToken(TokenType::FALSE, tokenPos, buffer);
	}
	else if (buffer == "var") {
		addToken(TokenType::VAR, tokenPos, buffer);
	}
	else if (buffer == "while") {
		addToken(TokenType::WHILE, tokenPos, buffer);
	}
	else if (buffer == "for") {
		addToken(TokenType::FOR, tokenPos, buffer);
	}
	else if (buffer == "do") {
		addToken(TokenType::DO_WHILE, tokenPos, buffer);
	}
	else if (buffer == "break") {
		addToken(TokenType::BREAK, tokenPos, buffer);
	}
	else if (buffer == "continue") {
		addToken(TokenType::CONTINUE, tokenPos, buffer);
	}
	else if (buffer == "function") {
		addToken(TokenType::FUNCTION, tokenPos, buffer);
	}
	else if (buffer == "return") {
		addToken(TokenType::RETURN, tokenPos, buffer);
	}
    else if (buffer == "const") {
        addToken(TokenType::CONST, tokenPos, buffer);
    }
	else {
		addToken(TokenType::WORD, tokenPos, buffer);
	}
}

void Lexer::tokenizeString() {
	TokenPosition tokenPos = currentPos;
	next();
	char current = peek();
	std::string buffer = "";

	while (true) {
		if (current == '\\') {
			current = next();

			switch (current)
			{
				case '"':  current = next(); buffer += '"';  continue;
				case 'r':  current = next(); buffer += '\r'; continue;
				case 'n':  current = next(); buffer += '\n'; continue;
				case 't':  current = next(); buffer += '\t'; continue;
				case 'v':  current = next(); buffer += '\v'; continue;
				case '\\': current = next(); buffer += '\\'; continue;
			}
		}

		if (current == '"') {
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
		if (operators.find(buffer + current) == operators.end() && buffer.size() != 0) {
			addToken(operators.at(buffer), tokenPos, buffer);
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
	switch (let)
	{
		case '+': return true;
		case '-': return true;
		case '*': return true;
		case '/': return true;
		case '%': return true;
		case '(': return true;
		case ')': return true;
		case '[': return true;
		case ']': return true;
		case '{': return true;
		case '}': return true;
		case '=': return true;
		case '&': return true;
		case '|': return true;
		case '!': return true;
		case '>': return true;
		case '<': return true;
		case ';': return true;
		case ':': return true;
		case ',': return true;
		case '.': return true;
		default: return false;
	}
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
    return let == '"';
}

std::vector<Token>& Lexer::tokenize() {
	while (position < length) {
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

	return tokens;
}