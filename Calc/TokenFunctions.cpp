// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "TokenFunctions.h"

std::string tokenTypeToString(const TokenType type) {
	switch (type) {
		case TokenType::NONE:                 return std::string("None");
		case TokenType::NUMBER:               return std::string("Number");
		case TokenType::WORD:                 return std::string("Word");
		case TokenType::STRING:               return std::string("String");
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
		case TokenType::END_OF_FILE:          return std::string("EOF");
		default:							  return std::string("Unknown token");
	}
}