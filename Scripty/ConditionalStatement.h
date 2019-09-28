#pragma once

#include "IStatement.h"
#include "IExpression.h"
#include <memory>

class ConditionalStatement : public IStatement {
private:
	std::unique_ptr<IExpression> expression;
	std::unique_ptr<IStatement> ifStatement;
	std::unique_ptr<IStatement> elseStatement;

public:
	ConditionalStatement(std::unique_ptr<IExpression>&& expression, std::unique_ptr<IStatement>&& ifStatement, std::unique_ptr<IStatement>&& elseStatement);
	virtual Action execute(Scope& scope) override;
	virtual void accept(IVisitor* visitor) override;
	virtual void innerAccept(IVisitor* visitor) override;
};