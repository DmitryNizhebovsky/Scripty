// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "Scope.h"

Scope::Scope() : parentScope(nullptr) {}

void Scope::setParentScope(Scope& parent) {
	parentScope = &parent;
}

void Scope::defineVariable(const std::string& name, Value&& value) {
    if (variables.find(name) == variables.end()) {
        variables.emplace(name, std::move(value));
    } else {
        throw std::runtime_error("Error: redeclaration of '" + name + "'");
    }
}

void Scope::defineFunction(const std::string& name, std::unique_ptr<IFunction>&& function) {
    if (functions.find(name) == functions.end()) {
        functions.emplace(name, std::move(function));
    } else {
        throw std::runtime_error("Error: redefinition  of '" + name + "'");
    }
}

IValue* Scope::getVariable(const std::string& name) const {
	if (variables.find(name) != variables.end()) {
		return variables.at(name)->getPtr();
	}
	else {
		if (parentScope != nullptr) {
			return parentScope->getVariable(name);
		}
		else {
			throw std::runtime_error("Unknown variable");
		}
	}
}

Value& Scope::getRefVariable(const std::string& name) {
	if (variables.find(name) != variables.end()) {
		return variables.at(name);
	}
	else {
		if (parentScope != nullptr) {
			return parentScope->getRefVariable(name);
		}
		else {
			throw std::runtime_error("Unknown variable");
		}
	}
}

Value Scope::getCopyVariable(const std::string& name) const {
	if (variables.find(name) != variables.end()) {
		return variables.at(name)->copy();
	}
	else {
		if (parentScope != nullptr) {
			return parentScope->getCopyVariable(name);
		}
		else {
			throw std::runtime_error("Unknown variable");
		}
	}
}

void Scope::setVariable(const std::string& name, Value&& value) {
	if (variables.find(name) != variables.end()) {
		variables.at(name) = std::move(value);
	}
	else {
		if (parentScope != nullptr) {
			return parentScope->setVariable(name, std::move(value));
		}
		else {
			throw std::runtime_error("Unknown variable");
		}
	}
}

IFunction* Scope::getFunction(const std::string& name) const {
	if (functions.find(name) != functions.end()) {
		return functions.at(name)->get();
	}
	else {
		if (parentScope != nullptr) {
			return parentScope->getFunction(name);
		}
		else {
			throw std::runtime_error("Unknown function");
		}
	}
}

void Scope::setFunction(const std::string& name, std::unique_ptr<IFunction>&& function) {
	if (functions.find(name) != functions.end()) {
		functions.at(name) = std::move(function);
	}
	else {
		if (parentScope != nullptr) {
			return parentScope->setFunction(name, std::move(function));
		}
		else {
			throw std::runtime_error("Unknown function");
		}
	}
}