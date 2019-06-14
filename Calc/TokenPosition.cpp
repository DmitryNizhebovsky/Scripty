#include "TokenPosition.h"

TokenPosition::TokenPosition() : row(0), column(0) {};
TokenPosition::TokenPosition(size_t row, size_t column) : row(row), column(column) {};

const std::string TokenPosition::toString() const {
	return std::string("[" + std::to_string(row) + ";" + std::to_string(column) + "]");
}