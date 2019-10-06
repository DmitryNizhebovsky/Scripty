#pragma once

#include "ActionType.h"
#include "IValue.h"
#include "NumberValue.h"
#include <memory>

class Action {
private:
	ActionType type;
	Value value;

public:
	Action(ActionType type);
	Action(ActionType type, Value&& value);
	ActionType getType() const;
	void setValue(Value&& value);
	Value getValue() const;
};