#pragma once

#include "IStatement.h"
#include "IExpression.h"
#include <memory>

class ReturnStatement : public IStatement {
private:
	std::unique_ptr<IExpression> expression;

public:
	ReturnStatement(std::unique_ptr<IExpression>&& expression);
	virtual Action execute(Scope& scope) override;
	virtual void accept(IVisitor* visitor) override;
	virtual void innerAccept(IVisitor* visitor) override;
};