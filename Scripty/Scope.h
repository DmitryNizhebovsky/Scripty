#pragma once

#include "IValue.h"
#include "IFunction.h"
#include <map>

class Scope {
private:
	std::map<std::string, Value>    variables;
	std::map<std::string, std::unique_ptr<IFunction>> functions;
	Scope* parentScope;

public:
	Scope();
	void setParentScope(Scope& parent);

	Value  getCopyVariable(const std::string& name) const;
	IValue* getVariable(const std::string& name) const;
	Value& getRefVariable(const std::string& name);
	void setVariable(const std::string& name, Value&& value);
	void defineVariable(const std::string& name, Value&& value);

	IFunction* getFunction(const std::string& name) const;
	void setFunction(const std::string& name, std::unique_ptr<IFunction>&& function);
	void defineFunction(const std::string& name, std::unique_ptr<IFunction>&& function);
};