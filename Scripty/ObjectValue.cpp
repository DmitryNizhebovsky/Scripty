// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "ObjectValue.h"
#include "LangException.h"

ObjectValue::ObjectValue(std::map<std::string, Value>&& newValue) :
    value(std::move(newValue)) {}

ObjectValue::ObjectValue(const std::map<std::string, Value>& newValue) {
    for (auto const&[key, val] : newValue) {
        value.insert(std::pair<std::string, Value>(key, val->copy()));
    }
}

Value ObjectValue::getValue(Value&& key) const {
    std::string attribute = key->asString();

    if (value.find(attribute) == value.end()) {
        throw LangException(ExceptionType::RuntimeError, "Attribute \"" + attribute + "\" does not exist");
    }

    return value.at(attribute)->copy();
}

Value& ObjectValue::getValueRef(Value&& key) {
    std::string attribute = key->asString();

    if (value.find(attribute) == value.end()) {
        value.insert(std::pair<std::string, Value>(attribute, nullptr));
    }

    return value[attribute];
}

double ObjectValue::asDouble() const {
    throw LangException(ExceptionType::RuntimeError, "Cannot cast object to number");
}

std::string ObjectValue::asString() const {
    std::string objectStr = "{\n";

    for (auto it = value.begin(); it != value.end(); ++it)
    {
        objectStr += "  " + it->first + ": " + it->second->asString();
        objectStr += it != std::prev(value.end()) ? ",\n" : "\n}";
    }

    return objectStr;
}

Value ObjectValue::copy() const {
    return std::make_unique<ObjectValue>(value);
}

ValueType ObjectValue::getValueType() const noexcept {
    return ValueType::Object;
}

IValue* ObjectValue::getPtr() {
    return this;
}