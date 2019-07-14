// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "UserFunctionDefine.h"

UserFunctionDefine::UserFunctionDefine(std::vector<std::string>&& argsNames, IStatement* body) :
	argsNames(std::move(argsNames)),
	body(body) {}

std::unique_ptr<IValue> UserFunctionDefine::eval(Scope& scope, const std::vector<std::unique_ptr<IValue>>&& args) {
	Action action = body->execute(scope);

	if (action.getType() == ActionType::RETURN) {
		return action.getValue();
	}

	return std::make_unique<NumberValue>(0.0);
}

IFunction* UserFunctionDefine::get() {
	return this;
}

size_t UserFunctionDefine::getArgsCount() const {
	return argsNames.size();
}

const std::string& UserFunctionDefine::getArgsName(size_t index) const {
	return argsNames[index];
}