// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "ArrayValue.h"
#include "LangException.h"

ArrayValue::ArrayValue(std::vector<std::unique_ptr<IValue>>&& newValue) :
    value(std::move(newValue)) {}

ArrayValue::ArrayValue(const std::vector<std::unique_ptr<IValue>>& newValue) {
    for (const auto& val : newValue) {
        value.emplace_back(val->copy());
    }
}

double ArrayValue::asDouble() const {
	throw LangException(ExceptionType::RuntimeError, "Cannot cast array to number");
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

std::unique_ptr<IValue> ArrayValue::copy() const {
    return std::make_unique<ArrayValue>(value);
}

IValue* ArrayValue::getPtr() {
	return this;
}

std::unique_ptr<IValue>& ArrayValue::getValueRef(int index) {
    if (index >= 0 && index < value.size()) {
        return value[index];
    } else {
        throw LangException(ExceptionType::RuntimeError, "Index out of range");
    }
}

std::unique_ptr<IValue> ArrayValue::getValue(int index) const {
    if (index >= 0 && index < value.size()) {
        return value[index]->copy();
    } else {
        throw LangException(ExceptionType::RuntimeError, "Index out of range");
    }
}