#pragma once

#include "IStatement.h"
#include "IExpression.h"

class VariableDefinitionStatement : public IStatement {
private:
	std::unique_ptr<IExpression> expression;
	std::string variable;

public:
	VariableDefinitionStatement(const std::string& variable, std::unique_ptr<IExpression>&& expression);
	virtual Action execute(Scope& scope) override;
	virtual void accept(IVisitor* visitor) override;
	virtual void innerAccept(IVisitor* visitor) override;
};