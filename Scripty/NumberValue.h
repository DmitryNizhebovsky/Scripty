#pragma once

#include "IValue.h"
#include "DataType.h"
#include <string>
#include <memory>

class NumberValue : public IValue {
private:
	double value;
    DataType type;

public:
	NumberValue(double newValue);
	virtual double asDouble() const override;
	virtual std::string asString() const override;
	virtual std::unique_ptr<IValue> copy() const override;
    virtual DataType getType() const override;
	virtual IValue* getPtr() override;
};