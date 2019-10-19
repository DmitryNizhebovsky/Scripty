#pragma once

#include "IValue.h"
#include <vector>
#include <string>

class Scope;

class IFunction : public NonCopyable {
public:
	IFunction() = default;

	virtual Value eval(Scope& scope, std::vector<Value>&& args) = 0;
	virtual IFunction* get() = 0;

    virtual std::string getName() const = 0;
    virtual size_t getArgsCount() const = 0;
    virtual std::string getArgsName(size_t index) const = 0;
    virtual size_t getMaxArgsCount() const = 0;
    virtual bool isFixedNumberArguments() const = 0;

	virtual ~IFunction() = default;
};