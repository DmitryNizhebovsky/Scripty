#pragma once

#include "IValue.h"
#include <vector>

class Scope;

class IFunction : public NonCopyable {
public:
	IFunction() = default;
	virtual Value eval(Scope& scope, const std::vector<Value>&& args) = 0;
	virtual IFunction* get() = 0;
	virtual ~IFunction() = default;
};