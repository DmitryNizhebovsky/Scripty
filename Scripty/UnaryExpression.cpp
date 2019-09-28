// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "UnaryExpression.h"

UnaryExpression::UnaryExpression(TokenType operation, std::unique_ptr<IExpression>&& expr):
	operation(operation),
	expr(std::move(expr)) {}

std::unique_ptr<IValue> UnaryExpression::eval(Scope& scope) {
	switch (operation) {
		case TokenType::LOGICAL_NOT:  return std::make_unique<NumberValue>( expr->eval(scope)->asDouble() > 0.0 ? 0.0 : 1.0);
		case TokenType::MINUS:        return std::make_unique<NumberValue>(-expr->eval(scope)->asDouble());
		case TokenType::PLUS:  
		default:                      return std::make_unique<NumberValue>(expr->eval(scope)->asDouble());
	}
}

void UnaryExpression::accept(IVisitor* visitor) {
	visitor->visit(*this);
}

void UnaryExpression::innerAccept(IVisitor* visitor) {
	expr->accept(visitor);
}