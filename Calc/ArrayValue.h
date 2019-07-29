#pragma once

#include "IValue.h"
#include <vector>

class ArrayValue : public IValue {
private:
	std::vector<std::unique_ptr<IValue>> value;

public:
	ArrayValue(std::vector<std::unique_ptr<IValue>>&& newValue);
    ArrayValue(const std::vector<std::unique_ptr<IValue>>& newValue);

    std::unique_ptr<IValue> getValue(int index) const;
    std::unique_ptr<IValue>& getValueRef(int index);

	virtual double asDouble() const override;
	virtual std::string asString() const override;
	virtual std::unique_ptr<IValue> copy() const override;
	virtual IValue* getPtr() override;
};