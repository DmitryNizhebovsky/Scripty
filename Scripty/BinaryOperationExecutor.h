#pragma once

#include "IValue.h"
#include "TokenType.h"
#include "ValueType.h"
#include <map>
#include <tuple>
#include <limits>

class BinaryOperationExecutor;

using FunctionPtr = Value(*)(const Value&, const Value&);
using Operation = std::tuple<TokenType, ValueType, ValueType>;
using BinaryOperationsTable = std::map<Operation, FunctionPtr>;

class BinaryOperationExecutor: public NonCopyable {
private:
    static BinaryOperationsTable binaryOperationsTable;
    static const double Epsilon;

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

    static Value binaryAndAnyAny(const Value& value1, const Value& value2);
    static Value binaryOrAnyAny(const Value& value1, const Value& value2);

    static Value binaryEqualsNumNum(const Value& value1, const Value& value2);
    static Value binaryNotEqualsNumNum(const Value& value1, const Value& value2);
    static Value binaryGreaterThanNumNum(const Value& value1, const Value& value2);
    static Value binaryLessThanNumNum(const Value& value1, const Value& value2);
    static Value binaryGreaterOrEqualsNumNum(const Value& value1, const Value& value2);
    static Value binaryLessOrEqualsNumNum(const Value& value1, const Value& value2);

    static Value binaryEqualsStrStr(const Value& value1, const Value& value2);
    static Value binaryNotEqualsStrStr(const Value& value1, const Value& value2);
    static Value binaryGreaterThanStrStr(const Value& value1, const Value& value2);
    static Value binaryLessThanStrStr(const Value& value1, const Value& value2);
    static Value binaryGreaterOrEqualsStrStr(const Value& value1, const Value& value2);
    static Value binaryLessOrEqualsStrStr(const Value& value1, const Value& value2);

    static Value makeBoolValue(bool value);
};