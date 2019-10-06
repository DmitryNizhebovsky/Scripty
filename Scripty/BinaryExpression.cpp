// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "BinaryExpression.h"
#include "BinaryOperationExecutor.h"

BinaryExpression::BinaryExpression(TokenType operation, std::unique_ptr<IExpression>&& expr1, std::unique_ptr<IExpression>&& expr2):
	operation(operation),
	expr1(std::move(expr1)),
	expr2(std::move(expr2)) {}

Value BinaryExpression::eval(Scope& scope) {
    Value value1 = expr1->eval(scope);
    Value value2 = expr2->eval(scope);

    return BinaryOperationExecutor::execute(operation, value1, value2);
}

void BinaryExpression::accept(IVisitor* visitor) {
	visitor->visit(*this);
}

void BinaryExpression::innerAccept(IVisitor* visitor) {
	expr1->accept(visitor);
	expr2->accept(visitor);
}