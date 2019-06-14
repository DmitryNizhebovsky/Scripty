// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "ConditionalStatement.h"

ConditionalStatement::ConditionalStatement(std::unique_ptr<IExpression>&& expression, std::unique_ptr<IStatement>&& ifStatement, std::unique_ptr<IStatement>&& elseStatement) :
	expression(std::move(expression)),
	ifStatement(std::move(ifStatement)),
	elseStatement(std::move(elseStatement)) {}

Action ConditionalStatement::execute(Scope& scope) {
	Scope localScope;
	localScope.setParentScope(scope);

	if (expression->eval(localScope)->asDouble() > 0.0) {
		return ifStatement->execute(localScope);
	}
	else if (elseStatement) {
		return elseStatement->execute(localScope);
	}

	return Action(ActionType::NONE);
}

void ConditionalStatement::accept(IVisitor* visitor) {
	visitor->visit(*this);
}

void ConditionalStatement::innerAccept(IVisitor* visitor) {
	expression->accept(visitor);
	ifStatement->accept(visitor);
	if (elseStatement) {
		elseStatement->accept(visitor);
	}
}