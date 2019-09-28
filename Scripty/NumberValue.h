#pragma once

#include "IValue.h"

class NumberValue : public IValue {
private:
	double value;

public:
	NumberValue(double newValue);
	virtual double asDouble() const override;
	virtual std::string asString() const override;
	virtual std::unique_ptr<IValue> copy() const override;
	virtual IValue* getPtr() override;
};