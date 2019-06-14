#include "BinaryExpression.h"

BinaryExpression::BinaryExpression(TokenType operation, std::unique_ptr<IExpression>&& expr1, std::unique_ptr<IExpression>&& expr2):
	operation(operation),
	expr1(std::move(expr1)),
	expr2(std::move(expr2)) {}

std::unique_ptr<IValue> BinaryExpression::eval(Scope& scope) {
	switch (operation) {
		case TokenType::PLUS:     return binaryAdd(expr1, expr2, scope);
		case TokenType::MINUS:    return binarySub(expr1, expr2, scope);
		case TokenType::MULTIPLY: return binaryMul(expr1, expr2, scope);
		case TokenType::DIVISION: return binaryDiv(expr1, expr2, scope);
		case TokenType::MOD:      return binaryMod(expr1, expr2, scope);
		case TokenType::DIV:      return binaryIntDiv(expr1, expr2, scope);
		default: throw std::runtime_error("Unknown operator");
	}
}

void BinaryExpression::accept(IVisitor* visitor) {
	visitor->visit(*this);
}

void BinaryExpression::innerAccept(IVisitor* visitor) {
	expr1->accept(visitor);
	expr2->accept(visitor);
}