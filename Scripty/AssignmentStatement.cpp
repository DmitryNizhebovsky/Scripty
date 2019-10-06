// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "AssignmentStatement.h"
#include "BinaryOperationExecutor.h"
#include "Token.h"
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

	Value& variable = lvalue->getRef(scope);
	variable = evalExpression(scope);
	return Action(ActionType::NONE);
}

Value AssignmentStatement::evalExpression(Scope& scope) {
    Value value1 = lexpr->eval(scope);
    Value value2 = rexpr->eval(scope);

    if (Token::isCompoundAssignmentOperator(assignType)) {
        TokenType binOperator = Token::convertCompoundAssignmentOperatorToBinaryOperator(assignType);
        return BinaryOperationExecutor::execute(binOperator, value1, value2);
    } else {
        return value2;
    }
}

void AssignmentStatement::accept(IVisitor* visitor) {
	visitor->visit(*this);
}

void AssignmentStatement::innerAccept(IVisitor* visitor) {
	lexpr->accept(visitor);
	rexpr->accept(visitor);
}