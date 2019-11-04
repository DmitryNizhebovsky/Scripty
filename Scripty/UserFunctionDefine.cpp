// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "UserFunctionDefine.h"

UserFunctionDefine::UserFunctionDefine(const std::string& name, std::vector<std::string>&& argsNames, IStatement* body, bool isFixedNumberArgs) :
    name(name),
	argsNames(std::move(argsNames)),
	body(body),
    isFixedNumberArgs(isFixedNumberArgs) {}

Value UserFunctionDefine::eval(Scope& scope, std::vector<Value>&& args) {
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

std::string UserFunctionDefine::getArgsName(size_t index) const {
	return argsNames[index];
}

std::string UserFunctionDefine::getName() const {
    return name;
}

size_t UserFunctionDefine::getMaxArgsCount() const {
    return argsNames.size();
}

bool UserFunctionDefine::isFixedNumberArguments() const {
    return isFixedNumberArgs;
}