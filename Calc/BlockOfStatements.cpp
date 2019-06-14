#include "BlockOfStatements.h"

void BlockOfStatements::addStatement(std::unique_ptr<IStatement>&& statement) {
	statements.emplace_back(std::move(statement));
}

void BlockOfStatements::insertStatement(std::unique_ptr<IStatement>&& statement, size_t index) {
	statements.insert(statements.begin() + index, std::move(statement));
}

Action BlockOfStatements::execute(Scope& scope) {
	Scope localScope;
	localScope.setParentScope(scope);

	for (auto& statement : statements) {
		Action action = statement->execute(localScope);

		if (action.getType() != ActionType::NONE) {
			return action;
		}
	}

	return Action(ActionType::NONE);
}

void BlockOfStatements::accept(IVisitor* visitor) {
	visitor->visit(*this);
}

void BlockOfStatements::innerAccept(IVisitor* visitor) {
	for (auto& statement : statements) {
		statement->accept(visitor);
	}
}