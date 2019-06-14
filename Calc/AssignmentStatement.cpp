// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "AssignmentStatement.h"
#include "BinaryOperations.h"
#include "Ilvalue.h"

AssignmentStatement::AssignmentStatement(TokenType assignType, std::unique_ptr<IExpression>&& lexpr, std::unique_ptr<IExpression>&& rexpr):
	assignType(assignType),
	lexpr(std::move(lexpr)),
	rexpr(std::move(rexpr)) {}

Action AssignmentStatement::execute(Scope& scope) {
	Ilvalue* lvalue = dynamic_cast<Ilvalue*>(lexpr.get());

	if (lvalue == nullptr) {
		throw std::runtime_error("Cannot assign to this expression");
	}

	std::unique_ptr<IValue>& variable = lvalue->getRef(scope);
	variable = evalExpression(scope);
	return Action(ActionType::NONE);
}

std::unique_ptr<IValue> AssignmentStatement::evalExpression(Scope& scope) {
	switch (assignType) {
		case TokenType::PLUS_ASSIGN:     return binaryAdd(lexpr, rexpr, scope);
		case TokenType::MINUS_ASSIGN:    return binarySub(lexpr, rexpr, scope);
		case TokenType::MULTIPLY_ASSIGN: return binaryMul(lexpr, rexpr, scope);
		case TokenType::DIVISION_ASSIGN: return binaryDiv(lexpr, rexpr, scope);
		case TokenType::MOD_ASSIGN:      return binaryMod(lexpr, rexpr, scope);
		case TokenType::DIV_ASSIGN:      return binaryIntDiv(lexpr, rexpr, scope);
		case TokenType::ASSIGN:
		default:                         return rexpr->eval(scope);
	}
}

void AssignmentStatement::accept(IVisitor* visitor) {
	visitor->visit(*this);
}

void AssignmentStatement::innerAccept(IVisitor* visitor) {
	lexpr->accept(visitor);
	rexpr->accept(visitor);
}