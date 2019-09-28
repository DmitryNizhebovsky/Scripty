// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "VariableExpression.h"

VariableExpression::VariableExpression(const std::string& name): name(name) {};

std::unique_ptr<IValue> VariableExpression::eval(Scope& scope) {
	return scope.getCopyVariable(name);
}

std::unique_ptr<IValue>& VariableExpression::getRef(Scope& scope) {
	return scope.getRefVariable(name);
}

void VariableExpression::accept(IVisitor* visitor) {
	visitor->visit(*this);
}

void VariableExpression::innerAccept(IVisitor* visitor) {}