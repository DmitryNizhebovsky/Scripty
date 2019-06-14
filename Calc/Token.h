#pragma once

#include <string>
#include <sstream>
#include <iomanip>
#include "TokenType.h"
#include "TokenPosition.h"

class Token {
private:
	std::string   value;
	TokenType     type;
	TokenPosition position;

public:
	Token(const TokenType type, const std::string& value = "");
	Token(const TokenType type, const std::string& value, const TokenPosition& pos);

	void setPosition(const TokenPosition& pos) noexcept;
	void setType(const TokenType type) noexcept;
	void setValue(const std::string& value) noexcept;

	const TokenPosition getPosition() const noexcept;
	const TokenType     getType()     const noexcept;
	const std::string   getValue()    const noexcept;
	const std::string   toString()    const noexcept;
};