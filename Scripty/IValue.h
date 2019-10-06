#pragma once

#include <string>
#include <memory>
#include "NonCopyable.h"
#include "ValueType.h"

class IValue;
using Value = std::unique_ptr<IValue>;

class IValue: public NonCopyable {
public:
    IValue() = default;

	virtual double asDouble() const = 0;
	virtual std::string asString() const = 0;
	virtual Value copy() const = 0;

    virtual ValueType getValueType() const noexcept = 0;
	virtual IValue* getPtr() = 0;

    virtual ~IValue() = default;
};