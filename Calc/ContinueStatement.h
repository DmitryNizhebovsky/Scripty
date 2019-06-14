#pragma once

#include "IStatement.h"

class ContinueStatement : public IStatement {
public:
	ContinueStatement() = default;
	virtual Action execute(Scope& scope) override;
	virtual void accept(IVisitor* visitor) override;
	virtual void innerAccept(IVisitor* visitor) override;
};