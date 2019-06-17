// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "Token.h"

Token::Token(const TokenType type, const std::string& value) :
	value(value),
	type(type) {}

Token::Token(const TokenType type, const std::string& value, const TokenPosition& pos):
	value(value),
	position(pos),
	type(type) {}

void Token::setPosition(const TokenPosition& pos) noexcept {
	this->position = pos;
}

void Token::setType(const TokenType type) noexcept {
	this->type = type;
}

void Token::setValue(const std::string& value) noexcept {
	this->value = value;
}

const TokenPosition Token::getPosition() const noexcept {
	return position;
}

const TokenType Token::getType() const noexcept {
	return type;
}

const std::string Token::getValue() const noexcept {
	return value;
}

const std::string Token::toString() const noexcept {
	std::stringstream stream;
	stream << std::setw(25) << std::left << Token::toString(type) << std::setw(20) << value << position.toString();
	return stream.str();
}

std::map<std::string, TokenType> Token::operators = {
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
    { "|",  TokenType::BAR },
    { "&",  TokenType::AMP },
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
};

std::map<std::string, TokenType> Token::keywords = {
    { "if",       TokenType::IF       },
    { "else",     TokenType::ELSE     },
    { "true",     TokenType::TRUE     },
    { "false",    TokenType::FALSE    },
    { "var",      TokenType::VAR      },
    { "const",    TokenType::CONST    },
    { "for",      TokenType::FOR      },
    { "while",    TokenType::WHILE    },
    { "do",       TokenType::DO_WHILE },
    { "break",    TokenType::BREAK    },
    { "continue", TokenType::CONTINUE },
    { "return",   TokenType::RETURN   },
    { "function", TokenType::FUNCTION }
};

bool Token::isOperator(const std::string& token) noexcept {
    return (operators.find(token) != operators.end());
}

bool Token::isKeyword(const std::string& token) noexcept {
    return (keywords.find(token) != keywords.end());
}

std::string Token::toString(const TokenType tokenType) noexcept {
    switch (tokenType) {
        case TokenType::NONE:                 return std::string("none");
        case TokenType::NUMBER:               return std::string("number");
        case TokenType::WORD:                 return std::string("identifier");
        case TokenType::STRING:               return std::string("string");
        case TokenType::ASSIGN:               return std::string("=");
        case TokenType::VAR:                  return std::string("var");
        case TokenType::IF:                   return std::string("if");
        case TokenType::ELSE:                 return std::string("else");
        case TokenType::TRUE:                 return std::string("true");
        case TokenType::FALSE:                return std::string("false");
        case TokenType::DO_WHILE:             return std::string("do while");
        case TokenType::WHILE:                return std::string("while");
        case TokenType::FOR:                  return std::string("for");
        case TokenType::BREAK:                return std::string("break");
        case TokenType::CONTINUE:             return std::string("continue");
        case TokenType::FUNCTION:             return std::string("function");
        case TokenType::RETURN:               return std::string("return");
        case TokenType::PLUS:                 return std::string("+");
        case TokenType::MINUS:                return std::string("-");
        case TokenType::MULTIPLY:             return std::string("*");
        case TokenType::DIVISION:             return std::string("/");
        case TokenType::MOD:                  return std::string("%");
        case TokenType::DIV:                  return std::string("//");
        case TokenType::PLUS_ASSIGN:          return std::string("+=");
        case TokenType::MINUS_ASSIGN:         return std::string("-=");
        case TokenType::MULTIPLY_ASSIGN:      return std::string("*=");
        case TokenType::DIVISION_ASSIGN:      return std::string("/=");
        case TokenType::MOD_ASSIGN:           return std::string("%=");
        case TokenType::DIV_ASSIGN:           return std::string("//=");
        case TokenType::GREATER_THAN:         return std::string(">");
        case TokenType::GREATER_OR_EQUALS:    return std::string(">=");
        case TokenType::LESS_THAN:            return std::string("<");
        case TokenType::LESS_OR_EQUALS:       return std::string("<=");
        case TokenType::EQUALS:               return std::string("==");
        case TokenType::NOT_EQUALS:           return std::string("!=");
        case TokenType::LOGICAL_NOT:          return std::string("not");
        case TokenType::LOGICAL_AND:          return std::string("and");
        case TokenType::LOGICAL_OR:           return std::string("or");
        case TokenType::OPEN_BRACKET:         return std::string("(");
        case TokenType::CLOSE_BRACKET:        return std::string(")");
        case TokenType::OPEN_BRACES:          return std::string("{");
        case TokenType::CLOSE_BRACES:         return std::string("}");
        case TokenType::COMMA:                return std::string(",");
        case TokenType::DOT:                  return std::string(".");
        case TokenType::COLON:                return std::string(":");
        case TokenType::SEMICOLON:            return std::string(";");
        case TokenType::OPEN_SQUARE_BRACKET:  return std::string("[");
        case TokenType::CLOSE_SQUARE_BRACKET: return std::string("]");
        case TokenType::END_OF_FILE:          return std::string("eof");
        default:							  return std::string("unknown token");
    }
}