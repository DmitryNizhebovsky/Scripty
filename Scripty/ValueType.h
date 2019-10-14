#pragma once

#include <string>

enum class ValueType {
    Any,
    String,
    Number,
    Array,
    Object
};

class ValueTypeConverter {
public:
    static std::string toString(const ValueType valueType) noexcept {
        switch (valueType)
        {
            case ValueType::String: return "string";
            case ValueType::Number: return "number";
            case ValueType::Object: return "object";
            case ValueType::Array:  return "array";
            case ValueType::Any:    return "any";
            default: return "";
        }
    }
};