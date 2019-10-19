#pragma once
#include "INode.h"
#include "Scope.h"

class IExpression : public INode, public NonCopyable {
public:
	IExpression() = default;
    virtual Value eval(Scope& scope) = 0;
    virtual ~IExpression() = default;
};