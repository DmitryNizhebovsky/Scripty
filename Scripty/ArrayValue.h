#pragma once

#include "IValue.h"
#include "DataType.h"
#include "ICollection.h"
#include <vector>
#include <memory>
#include <string>

class ArrayValue : public IValue, public ICollection {
private:
	std::vector<std::unique_ptr<IValue>> value;
    DataType type;

public:
	ArrayValue(std::vector<std::unique_ptr<IValue>>&& newValue);
    ArrayValue(const std::vector<std::unique_ptr<IValue>>& newValue);

    virtual std::unique_ptr<IValue> getValue(std::unique_ptr<IValue>&& index) const override;
    virtual std::unique_ptr<IValue>& getValueRef(std::unique_ptr<IValue>&& index) override;

	virtual double asDouble() const override;
	virtual std::string asString() const override;
	virtual std::unique_ptr<IValue> copy() const override;
    virtual DataType getType() const override;
	virtual IValue* getPtr() override;

private:
    size_t validateIndex(std::unique_ptr<IValue>&& index) const;
};