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
        throw std::runtime_error("Error: function '" + name + "' has already been defined");
    }
}

IValue* Scope::getVariable(const std::string& name) const {
    auto it = variables.find(name);

	if (it != variables.end()) {
		return it->second->getPtr();
	} else {
		if (parentScope != nullptr) {
			return parentScope->getVariable(name);
		} else {
			throw std::runtime_error("Error: unknown variable");
		}
	}
}

Value& Scope::getRefVariable(const std::string& name) {
    auto it = variables.find(name);

	if (it != variables.end()) {
		return it->second;
	} else {
		if (parentScope != nullptr) {
            return parentScope->getRefVariable(name);
		} else {
			throw std::runtime_error("Error: unknown variable");
		}
	}
}

Value Scope::getCopyVariable(const std::string& name) const {
    auto it = variables.find(name);

	if (it != variables.end()) {
		return it->second->copy();
	} else {
		if (parentScope != nullptr) {
            return parentScope->getCopyVariable(name);
		} else {
			throw std::runtime_error("Error: unknown variable");
		}
	}
}

void Scope::setVariable(const std::string& name, Value&& value) {
    auto it = variables.find(name);

	if (it != variables.end()) {
		it->second = std::move(value);
	} else {
		if (parentScope != nullptr) {
            return parentScope->setVariable(name, std::move(value));
		} else {
			throw std::runtime_error("Error: unknown variable");
		}
	}
}

IFunction* Scope::getFunction(const std::string& name) const {
    auto it = functions.find(name);

	if (it != functions.end()) {
		return it->second->get();
	} else {
		if (parentScope != nullptr) {
            return parentScope->getFunction(name);
		} else {
            return nullptr;
		}
	}
}

void Scope::setFunction(const std::string& name, std::unique_ptr<IFunction>&& function) {
    auto it = functions.find(name);

	if (it != functions.end()) {
		it->second = std::move(function);
	} else {
		if (parentScope != nullptr) {
            return parentScope->setFunction(name, std::move(function));
		} else {
			throw std::runtime_error("Unknown function");
		}
	}
}