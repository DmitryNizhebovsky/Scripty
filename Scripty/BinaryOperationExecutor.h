#pragma once

#include "IValue.h"
#include "TokenType.h"
#include "ValueType.h"
#include <map>
#include <tuple>

class BinaryOperationExecutor;

using FunctionPtr = Value(*)(const Value&, const Value&);
using Operation = std::tuple<TokenType, ValueType, ValueType>;
using BinaryOperationsTable = std::map<Operation, FunctionPtr>;

class BinaryOperationExecutor: public NonCopyable {
private:
    static BinaryOperationsTable binaryOperationsTable;

public:
    BinaryOperationExecutor() = default;

    static Value execute(const TokenType operation, const Value& value1, const Value& value2);

    ~BinaryOperationExecutor() = default;

private:
    static Value binaryAddNumNum(const Value& value1, const Value& value2);
    static Value binarySubNumNum(const Value& value1, const Value& value2);
    static Value binaryMulNumNum(const Value& value1, const Value& value2);
    static Value binaryDivNumNum(const Value& value1, const Value& value2);
    static Value binaryModNumNum(const Value& value1, const Value& value2);
    static Value binaryIntDivNumNum(const Value& value1, const Value& value2);

    static Value binaryAddStrStr(const Value& value1, const Value& value2);
    static Value binaryMulNumStr(const Value& value1, const Value& value2);
    static Value binaryMulStrNum(const Value& value1, const Value& value2);
};