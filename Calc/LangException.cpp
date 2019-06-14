#include "LangException.h"

LangException::LangException(const ExceptionType type, const std::string& message, const TokenPosition position) noexcept {
    errorMsg = exceptionTypeToString(type) + ": " + position.toString() + " " + message;
}

const char* LangException::what() const throw() {
    return errorMsg.c_str();
}