// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "ContinueStatement.h"

Action ContinueStatement::execute(Scope& scope) {
	return Action(ActionType::CONTINUE);
}

void ContinueStatement::accept(IVisitor* visitor) {
	visitor->visit(*this);
}

void ContinueStatement::innerAccept(IVisitor* visitor) {}