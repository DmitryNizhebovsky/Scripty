// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

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

BinaryOperationsTable BinaryExpression::binaryOperationsTable = {
    {{DataType::Number, DataType::Number}, binaryAdd},
    {{DataType::Number, DataType::Number}, binarySub},
    {{DataType::Number, DataType::Number}, binaryMul},
    {{DataType::Number, DataType::Number}, binaryDiv},
    {{DataType::Number, DataType::Number}, binaryMod},
    {{DataType::Number, DataType::Number}, binaryIntDiv},
    {{DataType::String, DataType::String}, binaryIntDiv},
    {{DataType::String, DataType::Number}, binaryIntDiv},
    {{DataType::Number, DataType::String}, binaryIntDiv},
    {{DataType::Number, DataType::Number}, binaryIntDiv},
    {{DataType::Number, DataType::Number}, binaryIntDiv}
};