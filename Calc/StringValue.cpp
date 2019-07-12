// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "StringValue.h"
#include "LangException.h"

StringValue::StringValue(const std::string& newValue) :
    value(newValue) {}

double StringValue::asDouble() const {
	return std::stod(value);
}

std::string StringValue::asString() const {
	return value;
}

std::unique_ptr<IValue> StringValue::copy() const {
	return std::make_unique<StringValue>(value);
}

IValue* StringValue::getPtr() {
	return this;
}

std::unique_ptr<IValue>& StringValue::getValueRef(int index) {
    throw LangException(ExceptionType::RuntimeError, "Unable to assign value");
}

std::unique_ptr<IValue> StringValue::getValue(int index) const {
    if (index >= 0 && index < value.size()) {
        return std::make_unique<StringValue>(value[index]);
    } else {
        throw LangException(ExceptionType::RuntimeError, "Index out of range");
    }
}