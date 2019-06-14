#pragma once

#include "IValue.h"
#include "IFunction.h"
#include <map>

class Scope {
private:
	std::map<std::string, std::unique_ptr<IValue>>    variables;
	std::map<std::string, std::unique_ptr<IFunction>> functions;
	Scope* parentScope;

public:
	Scope();
	void setParentScope(Scope& parent);

	std::unique_ptr<IValue>  getCopyVariable(const std::string& name) const;
	IValue* getVariable(const std::string& name) const;
	std::unique_ptr<IValue>& getRefVariable(const std::string& name);
	void setVariable(const std::string& name, std::unique_ptr<IValue>&& value);
	void defineVariable(const std::string& name, std::unique_ptr<IValue>&& value);

	IFunction* getFunction(const std::string& name) const;
	void setFunction(const std::string& name, std::unique_ptr<IFunction>&& function);
	void defineFunction(const std::string& name, std::unique_ptr<IFunction>&& function);
};