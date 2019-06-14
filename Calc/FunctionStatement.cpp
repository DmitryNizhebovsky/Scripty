#include "FunctionStatement.h"

FunctionStatement::FunctionStatement(std::unique_ptr<IExpression>&& function) : 
	function(std::move(function)) {}

Action FunctionStatement::execute(Scope& scope) {
	Scope localScope;
	localScope.setParentScope(scope);

	function->eval(localScope);
	return Action(ActionType::NONE);
}

void FunctionStatement::accept(IVisitor* visitor) {
	visitor->visit(*this);
}

void FunctionStatement::innerAccept(IVisitor* visitor) {
	function->accept(visitor);
}