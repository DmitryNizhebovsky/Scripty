#pragma once

#include <string>

class TokenPosition {
public:
	size_t row;
	size_t column;

public:
	TokenPosition();
	TokenPosition(size_t row, size_t column);
	const std::string toString() const;
};