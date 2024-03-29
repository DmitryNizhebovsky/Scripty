#pragma once
class ArrayExpression;
class ObjectExpression;
class BinaryExpression;
class ConditionalExpression;
class FunctionExpression;
class ArrayLikeAccessExpression;
class ObjectAccessExpression;
class UnaryExpression;
class ValueExpression;
class VariableExpression;

class AssignmentStatement;
class BlockOfStatements;
class BlockOfVariableStatements;
class BreakStatement;
class ConditionalStatement;
class ContinueStatement;
class DoWhileStatement;
class ForStatement;
class FunctionDefinitionStatement;
class FunctionStatement;
class ReturnStatement;
class VariableDefinitionStatement;
class WhileStatement;

class IVisitor {
public:
	IVisitor() = default;
	virtual void visit(ArrayExpression& expr) = 0;
    virtual void visit(ObjectExpression& expr) = 0;
	virtual void visit(BinaryExpression& expr) = 0;
	virtual void visit(ConditionalExpression& expr) = 0;
	virtual void visit(FunctionExpression& expr) = 0;
	virtual void visit(ArrayLikeAccessExpression& expr) = 0;
    virtual void visit(ObjectAccessExpression& expr) = 0;
	virtual void visit(UnaryExpression& expr) = 0;
	virtual void visit(ValueExpression& expr) = 0;
	virtual void visit(VariableExpression& expr) = 0;

	virtual void visit(AssignmentStatement& stat) = 0;
	virtual void visit(BlockOfStatements& stat) = 0;
	virtual void visit(BlockOfVariableStatements& stat) = 0;
	virtual void visit(BreakStatement& stat) = 0;
	virtual void visit(ConditionalStatement& stat) = 0;
	virtual void visit(ContinueStatement& stat) = 0;
	virtual void visit(DoWhileStatement& stat) = 0;
	virtual void visit(ForStatement& stat) = 0;
	virtual void visit(FunctionDefinitionStatement& stat) = 0;
	virtual void visit(FunctionStatement& stat) = 0;
	virtual void visit(ReturnStatement& stat) = 0;
	virtual void visit(VariableDefinitionStatement& stat) = 0;
	virtual void visit(WhileStatement& stat) = 0;

	virtual ~IVisitor() = default;
};