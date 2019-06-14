#pragma once

#include "IExpression.h"
#include "BinaryOperations.h"
#include "TokenType.h"
#include "NumberValue.h"
#include "StringValue.h"
#include <memory>
#include <stdexcept>

class BinaryExpression : public IExpression {
private:
	std::unique_ptr<IExpression> expr1;
	std::unique_ptr<IExpression> expr2;
	TokenType operation;

public:
	BinaryExpression(TokenType operation, std::unique_ptr<IExpression>&& expr1, std::unique_ptr<IExpression>&& expr2);
	virtual std::unique_ptr<IValue> eval(Scope& scope) override;
	virtual void accept(IVisitor* visitor) override;
	virtual void innerAccept(IVisitor* visitor) override;
};