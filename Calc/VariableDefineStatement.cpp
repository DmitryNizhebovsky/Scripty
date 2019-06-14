#include "VariableDefineStatement.h"

VariableDefineStatement::VariableDefineStatement(const std::string& variable, std::unique_ptr<IExpression>&& expression) :
	variable(variable),
	expression(std::move(expression)) {}

Action VariableDefineStatement::execute(Scope& scope) {
	scope.defineVariable(variable, expression->eval(scope));
	return Action(ActionType::NONE);
}

void VariableDefineStatement::accept(IVisitor* visitor) {
	visitor->visit(*this);
}

void VariableDefineStatement::innerAccept(IVisitor* visitor) {
	expression->accept(visitor);
}