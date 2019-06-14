#pragma once
#include <string>

enum class TokenType {
	NONE,
	NUMBER,
	WORD,
	STRING,
	ASSIGN,

	VAR,
	IF,
	ELSE,
	TRUE,
	FALSE,
	DO_WHILE,
	WHILE,
	FOR,
	BREAK,
	CONTINUE,
	FUNCTION,
	RETURN,
    CONST,

	PLUS,              // +
	MINUS,             // -
	MULTIPLY,          // *
	DIVISION,          // /
	MOD,               // %
	DIV,               // //

	PLUS_ASSIGN,       // +=
	MINUS_ASSIGN,      // -=
	MULTIPLY_ASSIGN,   // *=
	DIVISION_ASSIGN,   // /=
	MOD_ASSIGN,        // %=
	DIV_ASSIGN,        // //=

	GREATER_THAN,      // >
	GREATER_OR_EQUALS, // >=
	LESS_THAN,         // <
	LESS_OR_EQUALS,    // <=
	EQUALS,            // ==
	NOT_EQUALS,        // !=

	LOGICAL_NOT,       // not
	LOGICAL_AND,       // and
	LOGICAL_OR,        // or

	OPEN_BRACKET,      // (
	CLOSE_BRACKET,     // )

	OPEN_BRACES,       // {
	CLOSE_BRACES,      // }

	COMMA,             // ,
	DOT,               // .
	COLON,             // :
	SEMICOLON,         // ;

	OPEN_SQUARE_BRACKET,  // [
	CLOSE_SQUARE_BRACKET, // ]

	END_OF_FILE        // eof 
};

std::string tokenTypeToString(const TokenType type) noexcept;