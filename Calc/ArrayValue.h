#pragma once

#include "IValue.h"
#include "ICollection.h"
#include <vector>

class ArrayValue : public IValue, public ICollection {
private:
	std::vector<std::unique_ptr<IValue>> value;

public:
	ArrayValue(std::vector<std::unique_ptr<IValue>>&& newValue);
    ArrayValue(const std::vector<std::unique_ptr<IValue>>& newValue);

    virtual std::unique_ptr<IValue> getValue(std::unique_ptr<IValue>&& key) const override;
    virtual std::unique_ptr<IValue>& getValueRef(std::unique_ptr<IValue>&& key) override;

	virtual double asDouble() const override;
	virtual std::string asString() const override;
	virtual std::unique_ptr<IValue> copy() const override;
	virtual IValue* getPtr() override;
};