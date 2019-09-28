#pragma once

#include "IStatement.h"
#include "Scope.h"
#include <vector>
#include <memory>

class BlockOfStatements : public IStatement {
private:
	std::vector<std::unique_ptr<IStatement>> statements;

public:
	BlockOfStatements() = default;
	void addStatement(std::unique_ptr<IStatement>&& statement);
	void insertStatement(std::unique_ptr<IStatement>&& statement, size_t index = 0);
	virtual Action execute(Scope& scope) override;
	virtual void accept(IVisitor* visitor) override;
	virtual void innerAccept(IVisitor* visitor) override;
};