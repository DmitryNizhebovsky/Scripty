// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "FunctionDefinitionStatement.h"

FunctionDefinitionStatement::FunctionDefinitionStatement(const std::string& name, std::vector<std::string>&& argsNames, std::unique_ptr<IStatement>&& body, bool isFixedNumberArgs) :
	name(name),
	argsNames(std::move(argsNames)),
	body(std::move(body)),
    isFixedNumberArgs(isFixedNumberArgs) {}

Action FunctionDefinitionStatement::execute(Scope& scope) {
	scope.defineFunction(name, std::make_unique<UserFunctionDefine>(name, std::move(argsNames), body.get(), isFixedNumberArgs));
	return Action(ActionType::NONE);
}

void FunctionDefinitionStatement::accept(IVisitor* visitor) {
	visitor->visit(*this);
}

void FunctionDefinitionStatement::innerAccept(IVisitor* visitor) {
	body->accept(visitor);
}