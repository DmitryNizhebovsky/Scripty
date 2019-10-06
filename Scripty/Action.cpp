// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "Action.h"

Action::Action(ActionType type) :
	type(type),
    value(std::make_unique<NumberValue>(0.0)) {}

Action::Action(ActionType type, Value&& value) :
	type(type),
	value(std::move(value)) {}

ActionType Action::getType() const {
	return type;
}

Value Action::getValue() const {
	return value->copy();
}

void Action::setValue(Value&& value) {
	this->value = std::move(value);
}