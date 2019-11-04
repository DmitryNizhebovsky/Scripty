// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "VariableDefinitionStatement.h"

VariableDefinitionStatement::VariableDefinitionStatement(const std::string& variable, std::unique_ptr<IExpression>&& expression) :
	variable(variable),
	expression(std::move(expression)) {}

Action VariableDefinitionStatement::execute(Scope& scope) {
	scope.defineVariable(variable, expression->eval(scope));
	return Action(ActionType::NONE);
}

void VariableDefinitionStatement::accept(IVisitor* visitor) {
	visitor->visit(*this);
}

void VariableDefinitionStatement::innerAccept(IVisitor* visitor) {
	expression->accept(visitor);
}