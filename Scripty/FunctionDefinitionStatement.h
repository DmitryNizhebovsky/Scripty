#pragma once

#include "IStatement.h"
#include "UserFunctionDefine.h"
#include <string>
#include <vector>
#include <memory>

class FunctionDefinitionStatement : public IStatement {
private:
	std::string name;
	std::vector<std::string> argsNames;
	std::unique_ptr<IStatement> body;
    bool isFixedNumberArgs;

public:
	FunctionDefinitionStatement(const std::string& name, std::vector<std::string>&& argsNames, std::unique_ptr<IStatement>&& body, bool isFixedNumberArgs);
	virtual Action execute(Scope& scope) override;
	virtual void accept(IVisitor* visitor) override;
	virtual void innerAccept(IVisitor* visitor) override;
};
