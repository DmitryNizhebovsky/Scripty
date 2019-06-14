#pragma once

#include <string>
#include <memory>
#include <map>
#include "IValue.h"

class ObjectValue : public IValue {
public:
    std::map<std::string, std::unique_ptr<IValue>> values;

public:
    std::unique_ptr<IValue> getValue(const std::string& name);
    std::unique_ptr<IValue>& getValueRef(const std::string& attribute);

    void setValue(std::string& name, std::unique_ptr<IValue>&& value);

    virtual double asDouble() const override;
    virtual std::string asString() const override;
    virtual std::unique_ptr<IValue> copy() const override;
    virtual IValue* getPtr() override;

public:
    ObjectValue(std::map<std::string, std::unique_ptr<IValue>>&& tableValues);
    ObjectValue(const std::map<std::string, std::unique_ptr<IValue>>& tableValues);

    ObjectValue(ObjectValue&&) = default;
    ObjectValue& operator=(ObjectValue&&) = default;
};