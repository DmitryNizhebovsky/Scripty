#pragma once
#include "INode.h"
#include "Scope.h"

class IExpression : public INode {
public:
	IExpression() = default;
	IExpression(const IExpression&) = delete;
	IExpression& operator=(const IExpression&) = delete;
    virtual ~IExpression() = default;

    virtual std::unique_ptr<IValue> eval(Scope& scope) = 0;
};