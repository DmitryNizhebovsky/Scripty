// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "ArrayExpression.h"

ArrayExpression::ArrayExpression(std::vector<std::unique_ptr<IExpression>>&& expressions) :
	expressions(std::move(expressions)) {}

std::unique_ptr<IValue> ArrayExpression::eval(Scope& scope) {
	std::vector<std::unique_ptr<IValue>> values;

	for (auto& expression : expressions) {
		values.emplace_back(expression->eval(scope));
	}

	return std::make_unique<ArrayValue>(std::move(values));
}

void ArrayExpression::accept(IVisitor* visitor) {
	visitor->visit(*this);
}

void ArrayExpression::innerAccept(IVisitor* visitor) {
	for (auto& expression : expressions) {
		expression->accept(visitor);
	}
}