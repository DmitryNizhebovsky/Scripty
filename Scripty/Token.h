#pragma once

#include <string>
#include <sstream>
#include <iomanip>
#include <map>
#include "TokenType.h"
#include "TokenPosition.h"

class Token {
private:
	std::string   value;
	TokenType     type;
	TokenPosition position;

 public:
    static std::map<std::string, TokenType> operators;
    static std::map<std::string, TokenType> keywords;

public:
	Token(const TokenType type, const std::string& value = "");
	Token(const TokenType type, const std::string& value, const TokenPosition& pos);

	void setPosition(const TokenPosition& pos) noexcept;
	void setValue(const std::string& value) noexcept;
    void setType(const TokenType type) noexcept;

	const TokenPosition getPosition() const noexcept;
	const TokenType     getType()     const noexcept;
	const std::string   getValue()    const noexcept;
	const std::string   toString()    const noexcept;

    static std::string toString(const TokenType tokenType) noexcept;
    static bool isOperator(const std::string& token) noexcept;
    static bool isCompoundAssignmentOperator(const TokenType tokenType) noexcept;
    static TokenType convertCompoundAssignmentOperatorToBinaryOperator(const TokenType tokenType) noexcept;
    static bool isKeyword(const std::string& token) noexcept;
};