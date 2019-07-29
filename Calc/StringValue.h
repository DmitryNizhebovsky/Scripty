#pragma once

#include "IValue.h"

class StringValue : public IValue {
private:
	std::string value;

public:
	StringValue(const std::string& newValue);

    std::unique_ptr<IValue> getValue(int index) const;
    std::unique_ptr<IValue>& getValueRef(int index);

	virtual double asDouble() const override;
	virtual std::string asString() const override;
	virtual std::unique_ptr<IValue> copy() const override;
	virtual IValue* getPtr() override;
};