// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "NumberValue.h"

NumberValue::NumberValue(double value) : value(value) {}

double NumberValue::asDouble() const {
	return value;
}

std::string NumberValue::asString() const {
	return std::to_string(value);
}

std::unique_ptr<IValue> NumberValue::copy() const {
	return std::make_unique<NumberValue>(value);
}

IValue* NumberValue::getPtr() {
	return this;
}