#pragma once
#include "INode.h"
#include "Action.h"
#include "Scope.h"

class IStatement : public INode, public NonCopyable {
public:
	IStatement() = default;
    virtual Action execute(Scope& scope) = 0;
    virtual ~IStatement() = default;
};