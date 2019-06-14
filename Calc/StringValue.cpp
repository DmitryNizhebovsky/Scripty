// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

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