#pragma once

#include "IStatement.h"

class BreakStatement : public IStatement {
public:
	BreakStatement() = default;
	virtual Action execute(Scope& scope) override;
	virtual void accept(IVisitor* visitor) override;
	virtual void innerAccept(IVisitor* visitor) override;
};