#include "ContinueStatement.h"

Action ContinueStatement::execute(Scope& scope) {
	return Action(ActionType::CONTINUE);
}

void ContinueStatement::accept(IVisitor* visitor) {
	visitor->visit(*this);
}

void ContinueStatement::innerAccept(IVisitor* visitor) {}