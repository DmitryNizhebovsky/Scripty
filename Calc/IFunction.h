#pragma once

#include "IValue.h"
#include <vector>

class Scope;

class IFunction {
public:
	IFunction() = default;
	virtual std::unique_ptr<IValue> eval(Scope& scope, const std::vector<std::unique_ptr<IValue>>&& args) = 0;
	virtual IFunction* get() = 0;
	virtual ~IFunction() = default;

private:
	IFunction(const IFunction&) = delete;
	IFunction& operator=(const IFunction&) = delete;
};