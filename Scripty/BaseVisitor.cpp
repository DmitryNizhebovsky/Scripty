// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "BaseVisitor.h"
#include "ArrayExpression.h"
#include "ObjectExpression.h"
#include "BinaryExpression.h"
#include "FunctionExpression.h"
#include "ArrayLikeAccessExpression.h"
#include "UnaryExpression.h"
#include "ValueExpression.h"
#include "VariableExpression.h"
#include "AssignmentStatement.h"
#include "BlockOfStatements.h"
#include "BlockOfVariableStatements.h"
#include "BreakStatement.h"
#include "ConditionalStatement.h"
#include "ContinueStatement.h"
#include "DoWhileStatement.h"
#include "ForStatement.h"
#include "FunctionDefineStatement.h"
#include "FunctionStatement.h"
#include "ReturnStatement.h"
#include "VariableDefineStatement.h"
#include "WhileStatement.h"

void BaseVisitor::visit(ArrayExpression& expr) {
	expr.innerAccept(this);
}

void BaseVisitor::visit(ObjectExpression& expr) {
    expr.innerAccept(this);
}

void BaseVisitor::visit(BinaryExpression& expr) {
	expr.innerAccept(this);
}

void BaseVisitor::visit(FunctionExpression& expr) {
	expr.innerAccept(this);
}

void BaseVisitor::visit(ArrayLikeAccessExpression& expr) {
	expr.innerAccept(this);
}

void BaseVisitor::visit(UnaryExpression& expr) {
	expr.innerAccept(this);
}

void BaseVisitor::visit(ValueExpression& expr) {
	expr.innerAccept(this);
}

void BaseVisitor::visit(VariableExpression& expr) {
	expr.innerAccept(this);
}

void BaseVisitor::visit(AssignmentStatement& stat) {
	stat.innerAccept(this);
}

void BaseVisitor::visit(BlockOfStatements& stat) {
	stat.innerAccept(this);
}

void BaseVisitor::visit(BlockOfVariableStatements& stat) {
	stat.innerAccept(this);
}

void BaseVisitor::visit(BreakStatement& stat) {
	stat.innerAccept(this);
}

void BaseVisitor::visit(ConditionalStatement& stat) {
	stat.innerAccept(this);
}

void BaseVisitor::visit(ContinueStatement& stat) {
	stat.innerAccept(this);
}

void BaseVisitor::visit(DoWhileStatement& stat) {
	stat.innerAccept(this);
}

void BaseVisitor::visit(ForStatement& stat) {
	stat.innerAccept(this);
}

void BaseVisitor::visit(FunctionDefineStatement& stat) {
	stat.innerAccept(this);
}

void BaseVisitor::visit(FunctionStatement& stat) {
	stat.innerAccept(this);
}

void BaseVisitor::visit(ReturnStatement& stat) {
	stat.innerAccept(this);
}

void BaseVisitor::visit(VariableDefineStatement& stat) {
	stat.innerAccept(this);
}

void BaseVisitor::visit(WhileStatement& stat) {
	stat.innerAccept(this);
}