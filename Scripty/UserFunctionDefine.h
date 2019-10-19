#pragma once

#include "IFunction.h"
#include "IStatement.h"
#include "NumberValue.h"
#include "Action.h"
#include <vector>
#include <memory>

class UserFunctionDefine : public IFunction {
private:
    std::string name;
	std::vector<std::string> argsNames;
	IStatement* body;
    bool isFixedNumberArgs;

public:
	UserFunctionDefine(const std::string& name, std::vector<std::string>&& argsNames, IStatement* body, bool isFixedNumberArgs);

	virtual Value eval(Scope& scope, std::vector<Value>&& args) override;
	virtual IFunction* get() final override;

    virtual size_t getArgsCount() const final override;
    virtual std::string getArgsName(size_t index) const final override;
    virtual std::string getName() const final override;
    virtual size_t getMaxArgsCount() const override;
    virtual bool isFixedNumberArguments() const final override;
};