// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "TokenPosition.h"

TokenPosition::TokenPosition() : row(0), column(0) {};
TokenPosition::TokenPosition(size_t row, size_t column) : row(row), column(column) {};

const std::string TokenPosition::toString() const {
	return std::string("[" + std::to_string(row) + ";" + std::to_string(column) + "]");
}