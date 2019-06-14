#include "FunctionDefineStatement.h"

FunctionDefineStatement::FunctionDefineStatement(const std::string& name, std::vector<std::string>&& argsNames, std::unique_ptr<IStatement>&& body) :
	name(name),
	argsNames(std::move(argsNames)),
	body(std::move(body)) {}

Action FunctionDefineStatement::execute(Scope& scope) {
	scope.defineFunction(name, std::make_unique<UserFunctionDefine>(std::move(argsNames), std::move(body)));
	return Action(ActionType::NONE);
}

void FunctionDefineStatement::accept(IVisitor* visitor) {
	visitor->visit(*this);
}

void FunctionDefineStatement::innerAccept(IVisitor* visitor) {
	body->accept(visitor);
}