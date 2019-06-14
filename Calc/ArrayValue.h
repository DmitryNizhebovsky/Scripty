#pragma once

#include "IValue.h"
#include "LangException.h"
#include <vector>

class ArrayValue : public IValue {
private:
	std::vector<std::unique_ptr<IValue>> array;

public:
	ArrayValue(std::vector<std::unique_ptr<IValue>>&& value);
    ArrayValue(const std::vector<std::unique_ptr<IValue>>& value);

	virtual double asDouble() const override;
	virtual std::string asString() const override;
	virtual std::unique_ptr<IValue> copy() const override;
	virtual IValue* getPtr() override;
	
	std::unique_ptr<IValue> getValue(int index) const;
    std::unique_ptr<IValue>& getValueRef(int index);

    size_t size() const;

	void set(size_t index, std::unique_ptr<IValue>&& value);
	void push(std::unique_ptr<IValue>&& value);
	void pop(std::unique_ptr<IValue>&& value);
};