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