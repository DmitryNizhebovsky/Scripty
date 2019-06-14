// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "ExceptionType.h"

std::string exceptionTypeToString(const ExceptionType type) noexcept {
    switch (type)
    {
        case ExceptionType::ParserError:  return "ParserError";
        case ExceptionType::RuntimeError: return "RuntimeError";
        case ExceptionType::TypeError:    return "TypeError";
        default:                          return "Unknown error type";
    }
}