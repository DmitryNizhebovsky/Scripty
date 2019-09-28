#pragma once

#include "ICollection.h"
#include "IValue.h"
#include <string>
#include <map>

class ObjectValue : public IValue, public ICollection {
private:
    std::map<std::string, std::unique_ptr<IValue>> value;

public:
    ObjectValue(std::map<std::string, std::unique_ptr<IValue>>&& newValue);
    ObjectValue(const std::map<std::string, std::unique_ptr<IValue>>& newValue);

    virtual std::unique_ptr<IValue> getValue(std::unique_ptr<IValue>&& key) const override;
    virtual std::unique_ptr<IValue>& getValueRef(std::unique_ptr<IValue>&& key) override;

    virtual double asDouble() const override;
    virtual std::string asString() const override;
    virtual std::unique_ptr<IValue> copy() const override;
    virtual IValue* getPtr() override;
};