#include "WhileStatement.h"

WhileStatement::WhileStatement(std::unique_ptr<IExpression>&& condition, std::unique_ptr<IStatement>&& statement):
	condition(std::move(condition)),
	statement(std::move(statement)) {};

Action WhileStatement::execute(Scope& scope) {
	Scope localScope;
	localScope.setParentScope(scope);

	while (condition->eval(localScope)->asDouble() > 0.0) {
		Action action = statement->execute(localScope);

		if (action.getType() == ActionType::BREAK) {
			break;
		}

		if (action.getType() == ActionType::RETURN) {
			return action;
		}
	}

	return Action(ActionType::NONE);
}

void WhileStatement::accept(IVisitor* visitor) {
	visitor->visit(*this);
}

void WhileStatement::innerAccept(IVisitor* visitor) {
	condition->accept(visitor);
	statement->accept(visitor);
}