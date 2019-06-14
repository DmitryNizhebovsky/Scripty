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
	stream << std::setw(25) << std::left << tokenTypeToString(type) << std::setw(20) << value << position.toString();
	return stream.str();
}