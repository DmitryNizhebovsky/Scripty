// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "ForStatement.h"

ForStatement::ForStatement(std::unique_ptr<IStatement>&& initialization, std::unique_ptr<IExpression>&& termination, 
	                       std::unique_ptr<IStatement>&& increment, std::unique_ptr<IStatement>&& statement):
	initialization(std::move(initialization)),
	termination(std::move(termination)),
	increment(std::move(increment)),
	statement(std::move(statement)) {}

Action ForStatement::execute(Scope& scope) {
	Scope localScope;
	localScope.setParentScope(scope);
	
	for (initialization->execute(localScope); termination->eval(localScope)->asDouble() > 0.0; increment->execute(localScope)) {
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

void ForStatement::accept(IVisitor* visitor) {
	visitor->visit(*this);
}

void ForStatement::innerAccept(IVisitor* visitor) {
	initialization->accept(visitor);
	termination->accept(visitor);
	increment->accept(visitor);
	statement->accept(visitor);
}