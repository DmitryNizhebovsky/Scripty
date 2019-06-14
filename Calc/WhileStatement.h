#pragma once

#include "IStatement.h"
#include "IExpression.h"
#include <memory>

class WhileStatement : public IStatement {
private:
	std::unique_ptr<IStatement> statement;
	std::unique_ptr<IExpression> condition;

public:
	WhileStatement(std::unique_ptr<IExpression>&& condition, std::unique_ptr<IStatement>&& statement);
	virtual Action execute(Scope& scope) override;
	virtual void accept(IVisitor* visitor) override;
	virtual void innerAccept(IVisitor* visitor) override;
};