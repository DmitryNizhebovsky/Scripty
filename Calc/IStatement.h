#pragma once
#include "INode.h"
#include "Action.h"
#include "Scope.h"

class IStatement : public INode {
public:
	IStatement() = default;
	IStatement(const IStatement&) = delete;
	IStatement& operator=(const IStatement&) = delete;
    virtual ~IStatement() = default;

    virtual Action execute(Scope& scope) = 0;
};