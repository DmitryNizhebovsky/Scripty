#pragma once

#include "IValue.h"
#include "NumberValue.h"
#include "IExpression.h"
#include "TokenType.h"
#include <memory>

class UnaryExpression : public IExpression {
private:
	std::unique_ptr<IExpression> expr;
	TokenType operation;

public:
	UnaryExpression(TokenType operation, std::unique_ptr<IExpression>&& expr);
	virtual Value eval(Scope& scope) override;
	virtual void accept(IVisitor* visitor) override;
	virtual void innerAccept(IVisitor* visitor) override;
};