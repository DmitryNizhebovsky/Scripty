#include "ArrayValue.h"

ArrayValue::ArrayValue(std::vector<std::unique_ptr<IValue>>&& value) :
	array(std::move(value)) {}

ArrayValue::ArrayValue(const std::vector<std::unique_ptr<IValue>>& value) {
    for (const auto& val : value) {
        array.emplace_back(val->copy());
    }
}

double ArrayValue::asDouble() const {
	throw std::runtime_error("Cannot cast array to number");
}

std::string ArrayValue::asString() const {
	std::string result = "[";

	for (auto it = array.begin(); it != array.end(); ++it) {
		result += it == array.begin() ? "" : ", ";
        result += (*it)->asString();
	}

	result += "]";
	return result;
}

std::unique_ptr<IValue> ArrayValue::copy() const {
    return std::make_unique<ArrayValue>(array);
}

IValue* ArrayValue::getPtr() {
	return this;
}

std::unique_ptr<IValue>& ArrayValue::getValueRef(int index) {
    if (index >= 0 && index < array.size()) {
        return array[index];
    } else {
        throw LangException(ExceptionType::RuntimeError, "Index out of range");
    }
}

std::unique_ptr<IValue> ArrayValue::getValue(int index) const {
    if (index >= 0 && index < array.size()) {
        return array[index]->copy();
    } else {
        throw LangException(ExceptionType::RuntimeError, "Index out of range");
    }
}

void ArrayValue::set(size_t index, std::unique_ptr<IValue>&& value) {
	array[index] = std::move(value);
}

void ArrayValue::push(std::unique_ptr<IValue>&& value) {
	array.emplace_back(std::move(value));
}

void ArrayValue::pop(std::unique_ptr<IValue>&& value) {
	array.pop_back();
}

size_t ArrayValue::size() const {
	return array.size();
}