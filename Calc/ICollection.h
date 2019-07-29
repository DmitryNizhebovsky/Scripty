#pragma once

#include "IValue.h"

class ICollection : public NonCopyable {
public:
    ICollection() = default;
    virtual std::unique_ptr<IValue>  getValue(std::unique_ptr<IValue>&& key) const = 0;
    virtual std::unique_ptr<IValue>& getValueRef(std::unique_ptr<IValue>&& key) = 0;
    virtual ~ICollection() = default;
};