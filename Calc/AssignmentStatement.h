#pragma once

#include "IStatement.h"
#include "IExpression.h"
#include "TokenType.h"

class AssignmentStatement : public IStatement {
private:
	TokenType assignType;
	std::unique_ptr<IExpression> lexpr;
	std::unique_ptr<IExpression> rexpr;

public:
	AssignmentStatement(TokenType assignType, std::unique_ptr<IExpression>&& lexpr, std::unique_ptr<IExpression>&& rexpr);
	virtual Action execute(Scope& scope) override;
	virtual void accept(IVisitor* visitor) override;
	virtual void innerAccept(IVisitor* visitor) override;

private:
    std::unique_ptr<IValue> evalExpression(Scope& scope);
};