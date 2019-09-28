// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "DoWhileStatement.h"

DoWhileStatement::DoWhileStatement(std::unique_ptr<IExpression>&& condition, std::unique_ptr<IStatement>&& statement) :
	condition(std::move(condition)),
	statement(std::move(statement)) {};

Action DoWhileStatement::execute(Scope& scope) {
	Scope localScope;
	localScope.setParentScope(scope);

	do {
		Action action = statement->execute(localScope);

		if (action.getType() == ActionType::BREAK) {
			break;
		}

		if (action.getType() == ActionType::RETURN) {
			return action;
		}
	} while (condition->eval(localScope)->asDouble() > 0.0);

	return Action(ActionType::NONE);
}

void DoWhileStatement::accept(IVisitor* visitor) {
	visitor->visit(*this);
}

void DoWhileStatement::innerAccept(IVisitor* visitor) {
	condition->accept(visitor);
	statement->accept(visitor);
}