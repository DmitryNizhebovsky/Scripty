#pragma once

#include "IExpression.h"
#include "IValue.h"
#include "TokenType.h"
#include <memory>
#include <stdexcept>

class BinaryExpression : public IExpression {
private:
	std::unique_ptr<IExpression> expr1;
	std::unique_ptr<IExpression> expr2;
	TokenType operation;

public:
	BinaryExpression(TokenType operation, std::unique_ptr<IExpression>&& expr1, std::unique_ptr<IExpression>&& value2);
	virtual Value eval(Scope& scope) override;
	virtual void accept(IVisitor* visitor) override;
	virtual void innerAccept(IVisitor* visitor) override;
};