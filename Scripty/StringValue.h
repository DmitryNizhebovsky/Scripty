#pragma once

#include "IValue.h"
#include "ICollection.h"
#include "ValueType.h"
#include <string>
#include <memory>

class StringValue : public IValue, public ICollection {
private:
	std::string value;

public:
	StringValue(const std::string& newValue);

    virtual Value getValue(Value&& index) const override;
    virtual Value& getValueRef(Value&& index) override;

	virtual double asDouble() const override;
	virtual std::string asString() const override;
	virtual Value copy() const override;
    virtual ValueType getValueType() const noexcept override;
	virtual IValue* getPtr() override;

private:
    size_t validateIndex(Value&& index) const;
};