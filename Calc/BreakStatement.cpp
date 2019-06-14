#include "BreakStatement.h"

Action BreakStatement::execute(Scope& scope) {
	return Action(ActionType::BREAK);
}

void BreakStatement::accept(IVisitor* visitor) {
	visitor->visit(*this);
}

void BreakStatement::innerAccept(IVisitor* visitor) {}