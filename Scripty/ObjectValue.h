#pragma once

#include "ICollection.h"
#include "IValue.h"
#include "ValueType.h"
#include <string>
#include <memory>
#include <map>

class ObjectValue : public IValue, public ICollection {
private:
    std::map<std::string, Value> value;

public:
    ObjectValue(std::map<std::string, Value>&& newValue);
    ObjectValue(const std::map<std::string, Value>& newValue);

    virtual Value getValue(Value&& key) const override;
    virtual Value& getValueRef(Value&& key) override;

    virtual double asDouble() const override;
    virtual std::string asString() const override;
    virtual Value copy() const override;
    virtual ValueType getValueType() const noexcept override;
    virtual IValue* getPtr() override;
};