#pragma once

#include <string>
#include <memory>
#include "NonCopyable.h"
#include "DataType.h"

class IValue: public NonCopyable {
public:
    IValue() = default;
	virtual double asDouble() const = 0;
	virtual std::string asString() const = 0;
    virtual DataType getType() const = 0;
	virtual std::unique_ptr<IValue> copy() const = 0;
	virtual IValue* getPtr() = 0;
    virtual ~IValue() = default;
};