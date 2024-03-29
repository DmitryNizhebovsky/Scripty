// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "FunctionExpression.h"

FunctionExpression::FunctionExpression(const std::string& name, std::vector<std::unique_ptr<IExpression>>&& args) :
	name(name),
    arguments(std::move(args)) {}

Value FunctionExpression::eval(Scope& scope) {
	Scope localScope;
	localScope.setParentScope(scope);

	std::vector<Value> argumentValues;

	for (auto& argument : arguments) {
        argumentValues.emplace_back(argument->eval(scope));
	}

	IFunction* function = scope.getFunction(name);

    if (!function) {
        throw std::runtime_error("Error: could not find function '" + name + "'");
    }

    size_t argsCountPassed = arguments.size();
    size_t argsCountExpected = 0;

	if (function->isFixedNumberArguments()) {
        argsCountExpected = function->getArgsCount();
        checkNumberArgumentsPassed(argsCountExpected, argsCountPassed, function, false);

		for (size_t arg = 0; arg < argumentValues.size(); ++arg) {
			localScope.defineVariable(function->getArgsName(arg), std::move(argumentValues[arg]));
		}
	}
    else {
        argsCountExpected = function->getMaxArgsCount();
        checkNumberArgumentsPassed(argsCountExpected, argsCountPassed, function, true);
    }

	return function->eval(localScope, std::move(argumentValues));
}

void FunctionExpression::accept(IVisitor* visitor) {
	visitor->visit(*this);
}

void FunctionExpression::innerAccept(IVisitor* visitor) {
	for (auto& argument : arguments) {
        argument->accept(visitor);
	}
}

void FunctionExpression::checkNumberArgumentsPassed(size_t argsCountExpected, size_t argsCountPassed, IFunction* function, bool checkMax) const {
    if (argsCountPassed > argsCountExpected) {
        std::string funcName = function->getName();
        std::string argsExpected = std::to_string(argsCountExpected);
        std::string argsPassed = std::to_string(argsCountPassed);

        if(checkMax)
            throw std::runtime_error("Error: " + funcName + " expected at most " + argsExpected + " arguments, got " + argsPassed);
        else
            throw std::runtime_error("Error: " + funcName + "() takes " + argsExpected + " arguments but " + argsPassed + " were given");
    }
    else if (!checkMax && (argsCountPassed < argsCountExpected)) {
        std::string funcName = function->getName();
        std::string argsMissing = std::to_string(argsCountExpected - argsCountPassed);
        std::string missingArgsList = "";

        for (size_t arg = argsCountPassed; arg < argsCountExpected; ++arg) {
            missingArgsList += "'" + function->getArgsName(arg) + "'";

            if (arg != argsCountExpected - 1)
                missingArgsList += arg != argsCountExpected - 2 ? ", " : " and ";
        }

        throw std::runtime_error("Error: " + funcName + "() missing " + argsMissing + " required positional arguments: " + missingArgsList);
    }
}