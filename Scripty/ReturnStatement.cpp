// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "ReturnStatement.h"

ReturnStatement::ReturnStatement(std::unique_ptr<IExpression>&& expression) :
	expression(std::move(expression)) {}

Action ReturnStatement::execute(Scope& scope) {
    if (expression) {
        return Action(ActionType::RETURN, expression->eval(scope));
    }
    else {
        return Action(ActionType::RETURN);
    }
}

void ReturnStatement::accept(IVisitor* visitor) {
	visitor->visit(*this);
}

void ReturnStatement::innerAccept(IVisitor* visitor) {
	expression->accept(visitor);
}