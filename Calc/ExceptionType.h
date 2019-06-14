#pragma once
#include <string>

enum class ExceptionType {
    ParserError,
    RuntimeError,
    TypeError
};

std::string exceptionTypeToString(const ExceptionType type) noexcept;