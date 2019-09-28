// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "LangException.h"

LangException::LangException(const ExceptionType type, const std::string& message, const TokenPosition& position) noexcept {
    errorMsg = exceptionTypeToString(type) + ": " + position.toString() + " " + message;
}

const char* LangException::what() const throw() {
    return errorMsg.c_str();
}