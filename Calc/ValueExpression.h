#pragma once

#include "IValue.h"
#include "IExpression.h"
#include "NumberValue.h"
#include "StringValue.h"
#include "ArrayValue.h"
#include <memory>
#include <vector>

class ValueExpression : public IExpression {
private:
	std::unique_ptr<IValue> value;

public:
	ValueExpression(double value);
	ValueExpression(const std::string& value);
	ValueExpression(std::vector<std::unique_ptr<IValue>>&& value);
	virtual std::unique_ptr<IValue> eval(Scope& scope) override;
	virtual void accept(IVisitor* visitor) override;
	virtual void innerAccept(IVisitor* visitor) override;
};