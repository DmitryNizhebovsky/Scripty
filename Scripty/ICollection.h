#pragma once

#include "IValue.h"

class ICollection : public NonCopyable {
public:
    ICollection() = default;
    virtual Value  getValue(Value&& key) const = 0;
    virtual Value& getValueRef(Value&& key) = 0;
    virtual ~ICollection() = default;
};