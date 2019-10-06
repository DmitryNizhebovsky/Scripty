// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "BinaryOperationExecutor.h"
#include "Token.h"
#include "NumberValue.h"
#include "StringValue.h"

BinaryOperationsTable BinaryOperationExecutor::binaryOperationsTable = {
    {{TokenType::PLUS,     ValueType::Number, ValueType::Number}, &BinaryOperationExecutor::binaryAddNumNum},
    {{TokenType::MINUS,    ValueType::Number, ValueType::Number}, &BinaryOperationExecutor::binarySubNumNum},
    {{TokenType::MULTIPLY, ValueType::Number, ValueType::Number}, &BinaryOperationExecutor::binaryMulNumNum},
    {{TokenType::DIVISION, ValueType::Number, ValueType::Number}, &BinaryOperationExecutor::binaryDivNumNum},
    {{TokenType::MOD,      ValueType::Number, ValueType::Number}, &BinaryOperationExecutor::binaryModNumNum},
    {{TokenType::DIV,      ValueType::Number, ValueType::Number}, &BinaryOperationExecutor::binaryIntDivNumNum},

    {{TokenType::PLUS,     ValueType::String, ValueType::String}, &BinaryOperationExecutor::binaryAddStrStr},
    {{TokenType::MULTIPLY, ValueType::Number, ValueType::String}, &BinaryOperationExecutor::binaryMulNumStr},
    {{TokenType::MULTIPLY, ValueType::String, ValueType::Number}, &BinaryOperationExecutor::binaryMulStrNum}
};

Value BinaryOperationExecutor::execute(const TokenType operation, const Value& value1, const Value& value2) {
    ValueType type1 = value1->getValueType();
    ValueType type2 = value2->getValueType();

    auto binOperation = std::make_tuple(operation, type1, type2);
    auto functionPtr = binaryOperationsTable.find(binOperation);

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