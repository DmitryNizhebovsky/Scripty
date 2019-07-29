#pragma once

#include "IValue.h"
#include "ICollection.h"

class StringValue : public IValue, public ICollection {
private:
	std::string value;

public:
	StringValue(const std::string& newValue);

    virtual std::unique_ptr<IValue> getValue(std::unique_ptr<IValue>&& key) const override;
    virtual std::unique_ptr<IValue>& getValueRef(std::unique_ptr<IValue>&& key) override;

	virtual double asDouble() const override;
	virtual std::string asString() const override;
	virtual std::unique_ptr<IValue> copy() const override;
	virtual IValue* getPtr() override;
};