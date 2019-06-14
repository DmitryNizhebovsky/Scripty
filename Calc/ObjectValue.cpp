// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "ObjectValue.h"
#include "LangException.h"

ObjectValue::ObjectValue(std::map<std::string, std::unique_ptr<IValue>>&& tableValues) :
    values(std::move(tableValues)) {}

ObjectValue::ObjectValue(const std::map<std::string, std::unique_ptr<IValue>>& tableValues) {
    for (auto const&[key, val] : tableValues) {
        values.insert(std::pair<std::string, std::unique_ptr<IValue>>(key, val->copy()));
    }
}

std::unique_ptr<IValue> ObjectValue::getValue(const std::string& name) {
    if (values.find(name) == values.end()) {
        throw LangException(ExceptionType::RuntimeError, "Attribute " + name + " does not exist");
    }
    else {
        return values[name]->copy();
    }
}

void ObjectValue::setValue(std::string& name, std::unique_ptr<IValue>&& value) {
    if (values.find(name) == values.end()) {
        values.insert(std::pair<std::string, std::unique_ptr<IValue>>(name, std::move(value)));
    }
    else {
        values[name] = std::move(value);
    }
}

double ObjectValue::asDouble() const {
    throw LangException(ExceptionType::RuntimeError, "Cannot cast object to number");
}

std::string ObjectValue::asString() const {
    std::string objectStr = "{\n";

    for (auto const&[key, val] : values) {
        objectStr += "  " + key + ": " + val->asString() + ",\n";
    }

    objectStr = objectStr.substr(0, objectStr.length() - 2);
    objectStr += "\n}";

    return objectStr;
}

std::unique_ptr<IValue> ObjectValue::copy() const {
    return std::make_unique<ObjectValue>(values);
}

IValue* ObjectValue::getPtr() {
    return this;
}

std::unique_ptr<IValue>& ObjectValue::getValueRef(const std::string& attribute) {
    if (values.find(attribute) == values.end()) {
        values.insert(std::pair<std::string, std::unique_ptr<IValue>>(attribute, nullptr));
    }
    
    return values[attribute];
}