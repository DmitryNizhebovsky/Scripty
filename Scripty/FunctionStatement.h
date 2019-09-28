#pragma once

#include "IStatement.h"
#include "IExpression.h"
#include <memory>

class FunctionStatement : public IStatement {
private:
	std::unique_ptr<IExpression> function;

public:
	FunctionStatement(std::unique_ptr<IExpression>&& function);
	virtual Action execute(Scope& scope) override;
	virtual void accept(IVisitor* visitor) override;
	virtual void innerAccept(IVisitor* visitor) override;
};