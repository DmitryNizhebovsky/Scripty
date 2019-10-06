// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "FunctionalExpression.h"

FunctionalExpression::FunctionalExpression(const std::string& name) :
	name(name) {}

FunctionalExpression::FunctionalExpression(const std::string& name, std::vector<std::unique_ptr<IExpression>>&& args) :
	name(name),
	args(std::move(args)) {}

Value FunctionalExpression::eval(Scope& scope) {
	Scope localScope;
	localScope.setParentScope(scope);

	std::vector<Value> values;

	for (auto& arg : args) {
		values.emplace_back(arg->eval(scope));
	}

	IFunction* function = scope.getFunction(name);
	UserFunctionDefine* userFunction = dynamic_cast<UserFunctionDefine*>(function);

	if (userFunction) {
		if (userFunction->getArgsCount() != values.size()) {
			throw std::runtime_error("Arguments count mismatch");
		}

		for (size_t arg = 0; arg < values.size(); ++arg) {
			localScope.defineVariable(userFunction->getArgsName(arg), std::move(values[arg]));
		}
	}

	return function->eval(localScope, std::move(values));
}

void FunctionalExpression::addArgument(std::unique_ptr<IExpression>&& arg) {
	args.emplace_back(std::move(arg));
}

void FunctionalExpression::accept(IVisitor* visitor) {
	visitor->visit(*this);
}

void FunctionalExpression::innerAccept(IVisitor* visitor) {
	for (auto& arg : args) {
		arg->accept(visitor);
	}
}