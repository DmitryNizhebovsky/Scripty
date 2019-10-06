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

Value StringValue::copy() const {
	return std::make_unique<StringValue>(value);
}

ValueType StringValue::getValueType() const noexcept {
    return ValueType::String;
}

IValue* StringValue::getPtr() {
	return this;
}

Value& StringValue::getValueRef(Value&& index) {
    throw LangException(ExceptionType::RuntimeError, "Unable to assign value");
}

Value StringValue::getValue(Value&& index) const {
    size_t validIndex = validateIndex(std::move(index));
    return std::make_unique<StringValue>(std::string(1, value[validIndex]));
}

size_t StringValue::validateIndex(Value&& index) const {
    double dIndex = index->asDouble();

    if (dIndex < 0)
        throw LangException(ExceptionType::RuntimeError, "Index out of range");

    size_t sIndex = static_cast<size_t>(dIndex);

    if (sIndex >= value.size())
        throw LangException(ExceptionType::RuntimeError, "Index out of range");

    return sIndex;
}