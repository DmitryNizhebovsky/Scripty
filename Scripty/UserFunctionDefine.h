#pragma once

#include "IFunction.h"
#include "IStatement.h"
#include "NumberValue.h"
#include "Action.h"
#include <vector>
#include <memory>

class UserFunctionDefine : public IFunction {
private:
	std::vector<std::string> argsNames;
	IStatement* body;

public:
	UserFunctionDefine(std::vector<std::string>&& argsNames, IStatement* body);
	virtual Value eval(Scope& scope, const std::vector<Value>&& args) override;
	virtual IFunction* get() override;
	size_t getArgsCount() const;
	const std::string& getArgsName(size_t index) const;
};