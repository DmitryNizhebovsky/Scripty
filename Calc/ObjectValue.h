#pragma once

#include "IValue.h"
#include <string>
#include <map>

class ObjectValue : public IValue {
private:
    std::map<std::string, std::unique_ptr<IValue>> value;

public:
    ObjectValue(std::map<std::string, std::unique_ptr<IValue>>&& newValue);
    ObjectValue(const std::map<std::string, std::unique_ptr<IValue>>& newValue);

    std::unique_ptr<IValue> getValue(const std::string& attribute);
    std::unique_ptr<IValue>& getValueRef(const std::string& attribute);

    virtual double asDouble() const override;
    virtual std::string asString() const override;
    virtual std::unique_ptr<IValue> copy() const override;
    virtual IValue* getPtr() override;
};