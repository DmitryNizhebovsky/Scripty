#pragma once
#include "INode.h"
#include "Scope.h"

class IExpression : public INode {
public:
	IExpression() = default;
    virtual std::unique_ptr<IValue> eval(Scope& scope) = 0;
    virtual ~IExpression() = default;
};