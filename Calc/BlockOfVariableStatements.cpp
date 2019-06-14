#include "BlockOfVariableStatements.h"

void BlockOfVariableStatements::addStatement(std::unique_ptr<IStatement>&& statement) {
	statements.emplace_back(std::move(statement));
}

Action BlockOfVariableStatements::execute(Scope& scope) {
	for (auto& statement : statements) {
		statement->execute(scope);
	}

	return Action(ActionType::NONE);
}

void BlockOfVariableStatements::accept(IVisitor* visitor) {
	visitor->visit(*this);
}

void BlockOfVariableStatements::innerAccept(IVisitor* visitor) {
	for (auto& statement : statements) {
		statement->accept(visitor);
	}
}