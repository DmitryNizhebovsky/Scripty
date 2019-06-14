#include "StringValue.h"

StringValue::StringValue(std::string value) : value(value) {}

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