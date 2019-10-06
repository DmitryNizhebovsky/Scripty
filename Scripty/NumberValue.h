#pragma once

#include "IValue.h"
#include "ValueType.h"
#include <string>
#include <memory>

class NumberValue : public IValue {
private:
	double value;

public:
	NumberValue(double newValue);
	virtual double asDouble() const override;
	virtual std::string asString() const override;
	virtual Value copy() const override;
    virtual ValueType getValueType() const noexcept override;
	virtual IValue* getPtr() override;
};