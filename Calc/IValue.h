#pragma once

#include <string>
#include <memory>
#include "NonCopyable.h"

class IValue: public NonCopyable {
public:
	
	virtual double asDouble() const = 0;
	virtual std::string asString() const = 0;
	virtual std::unique_ptr<IValue> copy() const = 0;
	virtual IValue* getPtr() = 0;

public:
    IValue() = default;
    virtual ~IValue() = default;

	IValue(IValue&&) = default;
	IValue& operator=(IValue&&) = default;
};