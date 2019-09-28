#pragma once

class StringValue;

#include "IValue.h"

class ProxyStringItem : public IValue {
private:
    StringValue* stringValue;
    size_t itemIndex;

public:
    ProxyStringItem(StringValue* value, size_t index = 0);
    virtual double asDouble() const override;
    virtual std::string asString() const override;
    virtual std::unique_ptr<IValue> copy() const override;
    virtual IValue* getPtr() override;

    void setItemIndex(size_t index);

    IValue& operator=(const std::unique_ptr<IValue>& newValue);
    IValue& operator=(const std::unique_ptr<IValue>&& newValue);
};