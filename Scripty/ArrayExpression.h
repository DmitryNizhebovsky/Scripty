#pragma once

#include "IExpression.h"
#include "ArrayValue.h"
#include <vector>

class ArrayExpression : public IExpression {
private:
	std::vector<std::unique_ptr<IExpression>> expressions;

public:
	ArrayExpression(std::vector<std::unique_ptr<IExpression>>&& expressions);
	virtual Value eval(Scope& scope) override;
	virtual void accept(IVisitor* visitor) override;
	virtual void innerAccept(IVisitor* visitor) override;
};