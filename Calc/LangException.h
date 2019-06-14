#pragma once

#include "TokenPosition.h"
#include "ExceptionType.h"
#include <exception>
#include <string>

class LangException : public std::exception {
private:
	std::string errorMsg;

public:
    LangException(const ExceptionType type, const std::string& message, const TokenPosition position = TokenPosition(0, 0)) noexcept;
	virtual const char* what() const throw() override;
};