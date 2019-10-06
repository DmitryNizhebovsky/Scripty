// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "ArrayValue.h"
#include "LangException.h"

ArrayValue::ArrayValue(std::vector<Value>&& newValue) :
    value(std::move(newValue)) {}

ArrayValue::ArrayValue(const std::vector<Value>& newValue) {
    for (const auto& val : newValue) {
        value.emplace_back(val->copy());
    }
}

double ArrayValue::asDouble() const {
	throw LangException(ExceptionType::RuntimeError, "Cannot cast array to number");
}

ValueType ArrayValue::getValueType() const noexcept {
    return ValueType::Array;
}

std::string ArrayValue::asString() const {
	std::string result = "[";

	for (auto it = value.begin(); it != value.end(); ++it) {
		result += it == value.begin() ? "" : ", ";
        result += (*it)->asString();
	}

	result += "]";
	return result;
}

Value ArrayValue::copy() const {
    return std::make_unique<ArrayValue>(value);
}

IValue* ArrayValue::getPtr() {
	return this;
}

Value& ArrayValue::getValueRef(Value&& index) {
    size_t validIndex = validateIndex(std::move(index));
    return value[validIndex];
}

Value ArrayValue::getValue(Value&& index) const {
    size_t validIndex = validateIndex(std::move(index));
    return value[validIndex]->copy();
}

size_t ArrayValue::validateIndex(Value&& index) const {
    double dIndex = index->asDouble();

    if(dIndex < 0)
        throw LangException(ExceptionType::RuntimeError, "Index out of range");

    size_t sIndex = static_cast<size_t>(dIndex);

    if (sIndex >= value.size())
        throw LangException(ExceptionType::RuntimeError, "Index out of range");

    return sIndex;
}