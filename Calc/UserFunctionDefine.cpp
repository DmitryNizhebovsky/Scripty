#include "UserFunctionDefine.h"

UserFunctionDefine::UserFunctionDefine(std::vector<std::string>&& argsNames, std::unique_ptr<IStatement>&& body) :
	argsNames(std::move(argsNames)),
	body(std::move(body)) {}

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