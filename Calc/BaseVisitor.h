#pragma once
#include "IVisitor.h"

class BaseVisitor : public IVisitor {
public:
	virtual void visit(ArrayExpression& expr) override;
    virtual void visit(ObjectExpression& expr) override;
	virtual void visit(BinaryExpression& expr) override;
	virtual void visit(ConditionalExpression& expr) override;
	virtual void visit(FunctionalExpression& expr) override;
	virtual void visit(ArrayLikeAccessExpression& expr) override;
    virtual void visit(ObjectAccessExpression& expr) override;
	virtual void visit(UnaryExpression& expr) override;
	virtual void visit(ValueExpression& expr) override;
	virtual void visit(VariableExpression& expr) override;
	virtual void visit(AssignmentStatement& stat) override;
	virtual void visit(BlockOfStatements& stat) override;
	virtual void visit(BlockOfVariableStatements& stat) override;
	virtual void visit(BreakStatement& stat) override;
	virtual void visit(ConditionalStatement& stat) override;
	virtual void visit(ContinueStatement& stat) override;
	virtual void visit(DoWhileStatement& stat) override;
	virtual void visit(ForStatement& stat) override;
	virtual void visit(FunctionDefineStatement& stat) override;
	virtual void visit(FunctionStatement& stat) override;
	virtual void visit(ReturnStatement& stat) override;
	virtual void visit(VariableDefineStatement& stat) override;
	virtual void visit(WhileStatement& stat) override;
};