#pragma once

#include <string>
#include <memory>
#include <map>
#include "IValue.h"

class ObjectValue : public IValue {
private:
    std::map<std::string, std::unique_ptr<IValue>> value;

public:
    std::unique_ptr<IValue> getValue(const std::string& attribute);
    std::unique_ptr<IValue>& getValueRef(const std::string& attribute);

    virtual double asDouble() const override;
    virtual std::string asString() const override;
    virtual std::unique_ptr<IValue> copy() const override;
    virtual IValue* getPtr() override;

public:
    ObjectValue(std::map<std::string, std::unique_ptr<IValue>>&& newValue);
    ObjectValue(const std::map<std::string, std::unique_ptr<IValue>>& newValue);

    ObjectValue(ObjectValue&&) = default;
    ObjectValue& operator=(ObjectValue&&) = default;
};