// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "ValueExpression.h"

ValueExpression::ValueExpression(double value): 
	value(std::make_unique<NumberValue>(value)) {}

ValueExpression::ValueExpression(const std::string& value):
	value(std::make_unique<StringValue>(value)) {}

ValueExpression::ValueExpression(std::vector<std::unique_ptr<IValue>>&& value):
	value(std::make_unique<ArrayValue>(std::move(value))) {}

std::unique_ptr<IValue> ValueExpression::eval(Scope& scope) {
	return value->copy();
}

void ValueExpression::accept(IVisitor* visitor) {
	visitor->visit(*this);
}

void ValueExpression::innerAccept(IVisitor* visitor) {}