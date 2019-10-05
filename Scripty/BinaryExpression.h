#pragma once

#include "IExpression.h"
#include "BinaryOperations.h"
#include "TokenType.h"
#include "NumberValue.h"
#include "StringValue.h"
#include "DataType.h"
#include <memory>
#include <stdexcept>
#include <map>
#include <utility>

using FunctionPtr = std::unique_ptr<IValue>(*)(std::unique_ptr<IValue>&, std::unique_ptr<IValue>&);
using BinaryOperationsTable = std::map<std::pair<DataType, DataType>, FunctionPtr>;

class BinaryExpression : public IExpression {
private:
	std::unique_ptr<IExpression> expr1;
	std::unique_ptr<IExpression> expr2;
	TokenType operation;
    static BinaryOperationsTable binaryOperationsTable;

public:
	BinaryExpression(TokenType operation, std::unique_ptr<IExpression>&& expr1, std::unique_ptr<IExpression>&& expr2);
	virtual std::unique_ptr<IValue> eval(Scope& scope) override;
	virtual void accept(IVisitor* visitor) override;
	virtual void innerAccept(IVisitor* visitor) override;
};