#pragma once

#include "IStatement.h"
#include "IExpression.h"
#include <memory>

class ForStatement : public IStatement {
private:
	std::unique_ptr<IStatement>  initialization;
	std::unique_ptr<IExpression> termination;
	std::unique_ptr<IStatement>  increment;
	std::unique_ptr<IStatement>  statement;

public:
	ForStatement(std::unique_ptr<IStatement>&& initialization, std::unique_ptr<IExpression>&& termination, std::unique_ptr<IStatement>&& increment, std::unique_ptr<IStatement>&& statement);
	virtual Action execute(Scope& scope) override;
	virtual void accept(IVisitor* visitor) override;
	virtual void innerAccept(IVisitor* visitor) override;
};