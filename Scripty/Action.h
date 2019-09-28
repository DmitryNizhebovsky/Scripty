#pragma once

#include "ActionType.h"
#include "IValue.h"
#include "NumberValue.h"
#include <memory>

class Action {
private:
	ActionType type;
	std::unique_ptr<IValue> value;

public:
	Action(ActionType type);
	Action(ActionType type, std::unique_ptr<IValue>&& value);
	ActionType getType() const;
	void setValue(std::unique_ptr<IValue>&& value);
	std::unique_ptr<IValue> getValue() const;
};