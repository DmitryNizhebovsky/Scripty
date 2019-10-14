// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "BinaryOperationExecutor.h"
#include "Token.h"
#include "NumberValue.h"
#include "StringValue.h"

const double BinaryOperationExecutor::Epsilon = std::numeric_limits<double>::epsilon();

BinaryOperationsTable BinaryOperationExecutor::binaryOperationsTable = {
    {{TokenType::PLUS,     ValueType::Number, ValueType::Number}, &BinaryOperationExecutor::binaryAddNumNum},
    {{TokenType::MINUS,    ValueType::Number, ValueType::Number}, &BinaryOperationExecutor::binarySubNumNum},
    {{TokenType::MULTIPLY, ValueType::Number, ValueType::Number}, &BinaryOperationExecutor::binaryMulNumNum},
    {{TokenType::DIVISION, ValueType::Number, ValueType::Number}, &BinaryOperationExecutor::binaryDivNumNum},
    {{TokenType::MOD,      ValueType::Number, ValueType::Number}, &BinaryOperationExecutor::binaryModNumNum},
    {{TokenType::DIV,      ValueType::Number, ValueType::Number}, &BinaryOperationExecutor::binaryIntDivNumNum},

    {{TokenType::PLUS,     ValueType::String, ValueType::String}, &BinaryOperationExecutor::binaryAddStrStr},
    {{TokenType::MULTIPLY, ValueType::Number, ValueType::String}, &BinaryOperationExecutor::binaryMulNumStr},
    {{TokenType::MULTIPLY, ValueType::String, ValueType::Number}, &BinaryOperationExecutor::binaryMulStrNum},

    {{TokenType::LOGICAL_AND,       ValueType::Any, ValueType::Any}, &BinaryOperationExecutor::binaryAndAnyAny},
    {{TokenType::LOGICAL_OR,        ValueType::Any, ValueType::Any}, &BinaryOperationExecutor::binaryOrAnyAny},

    {{TokenType::EQUALS,            ValueType::Number, ValueType::Number}, &BinaryOperationExecutor::binaryEqualsNumNum},
    {{TokenType::NOT_EQUALS,        ValueType::Number, ValueType::Number}, &BinaryOperationExecutor::binaryNotEqualsNumNum},
    {{TokenType::GREATER_OR_EQUALS, ValueType::Number, ValueType::Number}, &BinaryOperationExecutor::binaryGreaterOrEqualsNumNum},
    {{TokenType::LESS_OR_EQUALS,    ValueType::Number, ValueType::Number}, &BinaryOperationExecutor::binaryLessOrEqualsNumNum},
    {{TokenType::GREATER_THAN,      ValueType::Number, ValueType::Number}, &BinaryOperationExecutor::binaryGreaterThanNumNum},
    {{TokenType::LESS_THAN,         ValueType::Number, ValueType::Number}, &BinaryOperationExecutor::binaryLessThanNumNum},

    {{TokenType::EQUALS,            ValueType::String, ValueType::String}, &BinaryOperationExecutor::binaryEqualsStrStr},
    {{TokenType::NOT_EQUALS,        ValueType::String, ValueType::String}, &BinaryOperationExecutor::binaryNotEqualsStrStr},
    {{TokenType::GREATER_OR_EQUALS, ValueType::String, ValueType::String}, &BinaryOperationExecutor::binaryGreaterOrEqualsStrStr},
    {{TokenType::LESS_OR_EQUALS,    ValueType::String, ValueType::String}, &BinaryOperationExecutor::binaryLessOrEqualsStrStr},
    {{TokenType::GREATER_THAN,      ValueType::String, ValueType::String}, &BinaryOperationExecutor::binaryGreaterThanStrStr},
    {{TokenType::LESS_THAN,         ValueType::String, ValueType::String}, &BinaryOperationExecutor::binaryLessThanStrStr}
};

Value BinaryOperationExecutor::execute(const TokenType operation, const Value& value1, const Value& value2) {
    ValueType type1 = value1->getValueType();
    ValueType type2 = value2->getValueType();

    auto binOperation = std::make_tuple(operation, type1, type2);
    auto functionPtr = binaryOperationsTable.find(binOperation);

    if (functionPtr == binaryOperationsTable.end()) {
        binOperation = std::make_tuple(operation, ValueType::Any, ValueType::Any);
        functionPtr = binaryOperationsTable.find(binOperation);
    }

    if (functionPtr != binaryOperationsTable.end()) {
        return functionPtr->second(value1, value2);
    }
    else {
        std::string opName = Token::toString(operation);
        std::string vType1 = ValueTypeConverter::toString(type1);
        std::string vType2 = ValueTypeConverter::toString(type2);

        throw std::runtime_error("Unsupported operand type(s) for " + opName + " : '" + vType1 + "' and '" + vType2 + "'");
    }
}

Value BinaryOperationExecutor::binaryEqualsNumNum(const Value& value1, const Value& value2) {
    return makeBoolValue(std::abs(value1->asDouble() - value2->asDouble()) < Epsilon);
}

Value BinaryOperationExecutor::binaryNotEqualsNumNum(const Value& value1, const Value& value2) {
    return makeBoolValue(std::abs(value1->asDouble() - value2->asDouble()) > Epsilon);
}

Value BinaryOperationExecutor::binaryGreaterThanNumNum(const Value& value1, const Value& value2) {
    return makeBoolValue(value1->asDouble() > value2->asDouble());
}

Value BinaryOperationExecutor::binaryLessThanNumNum(const Value& value1, const Value& value2) {
    return makeBoolValue(value1->asDouble() < value2->asDouble());
}

Value BinaryOperationExecutor::binaryGreaterOrEqualsNumNum(const Value& value1, const Value& value2) {
    return makeBoolValue(value1->asDouble() >= value2->asDouble());
}

Value BinaryOperationExecutor::binaryLessOrEqualsNumNum(const Value& value1, const Value& value2) {
    return makeBoolValue(value1->asDouble() <= value2->asDouble());
}

Value BinaryOperationExecutor::binaryAndAnyAny(const Value& value1, const Value& value2) {
    return std::make_unique<NumberValue>(value1->asBool() && value2->asBool());
}

Value BinaryOperationExecutor::binaryOrAnyAny(const Value& value1, const Value& value2) {
    return std::make_unique<NumberValue>(value1->asBool() || value2->asBool());
}

Value BinaryOperationExecutor::binaryEqualsStrStr(const Value& value1, const Value& value2) {
    return makeBoolValue(value1->asString() == value2->asString());
}

Value BinaryOperationExecutor::binaryNotEqualsStrStr(const Value& value1, const Value& value2) {
    return makeBoolValue(value1->asString() != value2->asString());
}

Value BinaryOperationExecutor::binaryGreaterThanStrStr(const Value& value1, const Value& value2) {
    return makeBoolValue(value1->asString() > value2->asString());
}

Value BinaryOperationExecutor::binaryLessThanStrStr(const Value& value1, const Value& value2) {
    return makeBoolValue(value1->asString() < value2->asString());
}

Value BinaryOperationExecutor::binaryGreaterOrEqualsStrStr(const Value& value1, const Value& value2) {
    return makeBoolValue(value1->asString() >= value2->asString());
}

Value BinaryOperationExecutor::binaryLessOrEqualsStrStr(const Value& value1, const Value& value2) {
    return makeBoolValue(value1->asString() <= value2->asString());
}

Value BinaryOperationExecutor::binaryAddNumNum(const Value& value1, const Value& value2) {
    return std::make_unique<NumberValue>(value1->asDouble() + value2->asDouble());
}

Value BinaryOperationExecutor::binarySubNumNum(const Value& value1, const Value& value2) {
    return std::make_unique<NumberValue>(value1->asDouble() - value2->asDouble());
}

Value BinaryOperationExecutor::binaryMulNumNum(const Value& value1, const Value& value2) {
    return std::make_unique<NumberValue>(value1->asDouble() * value2->asDouble());
}

Value BinaryOperationExecutor::binaryDivNumNum(const Value& value1, const Value& value2) {
    return std::make_unique<NumberValue>(value1->asDouble() / value2->asDouble());
}

Value BinaryOperationExecutor::binaryModNumNum(const Value& value1, const Value& value2) {
    int number1 = static_cast<int>(value1->asDouble());
    int number2 = static_cast<int>(value2->asDouble());
    double result = static_cast<double>(number1 % number2);

    return std::make_unique<NumberValue>(result);
}

Value BinaryOperationExecutor::binaryIntDivNumNum(const Value& value1, const Value& value2) {
    int number1 = static_cast<int>(value1->asDouble());
    int number2 = static_cast<int>(value2->asDouble());
    double result  = static_cast<double>(number1 / number2);

    return std::make_unique<NumberValue>(result);
}

Value BinaryOperationExecutor::binaryMulNumStr(const Value& value1, const Value& value2) {
    int count = 0;
    std::string buffer = "";
    std::string pattern = "";

    count = static_cast<int>(value1->asDouble());
    pattern = value2->asString();

    for (int i = 0; i < count; ++i) {
        buffer += pattern;
    }

    return std::make_unique<StringValue>(buffer);
}

Value BinaryOperationExecutor::binaryMulStrNum(const Value& value1, const Value& value2) {
    return binaryMulNumStr(value2, value1);
}

Value BinaryOperationExecutor::binaryAddStrStr(const Value& value1, const Value& value2) {
    return std::make_unique<StringValue>(value1->asString() + value2->asString());
}

Value BinaryOperationExecutor::makeBoolValue(bool value) {
    return std::make_unique<NumberValue>(value ? 1.0 : 0.0);
}