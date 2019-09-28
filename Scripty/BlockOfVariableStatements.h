#pragma once

#include "IStatement.h"
#include "Scope.h"
#include <vector>
#include <memory>

class BlockOfVariableStatements : public IStatement {
private:
	std::vector<std::unique_ptr<IStatement>> statements;

public:
	BlockOfVariableStatements() = default;
	void addStatement(std::unique_ptr<IStatement>&& statement);
	virtual Action execute(Scope& scope) override;
	virtual void accept(IVisitor* visitor) override;
	virtual void innerAccept(IVisitor* visitor) override;
};