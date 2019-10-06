// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "ConditionalExpression.h"

ConditionalExpression::ConditionalExpression(TokenType operation, std::unique_ptr<IExpression>&& expr1, std::unique_ptr<IExpression>&& expr2) :
	operation(operation),
	expr1(std::move(expr1)),
	expr2(std::move(expr2)) {}

Value ConditionalExpression::eval(Scope& scope) {
	Value value1 = expr1->eval(scope);
	Value value2 = expr2->eval(scope);

	double number1 = 0.0;
	double number2 = 0.0;
	bool result = false;

	if (dynamic_cast<StringValue*>(value1.get()) != NULL || dynamic_cast<StringValue*>(value2.get()) != NULL) {
		number1 = (double)value1->asString().compare(value2->asString());
		number2 = 0.0;
	}

	if (dynamic_cast<NumberValue*>(value1.get()) != NULL && dynamic_cast<NumberValue*>(value2.get()) != NULL) {
		number1 = value1->asDouble();
		number2 = value2->asDouble();
	}

	switch (operation) {
		case TokenType::GREATER_THAN:      result = number1 >  number2; break;
		case TokenType::LESS_THAN:         result = number1 <  number2; break;
		case TokenType::GREATER_OR_EQUALS: result = number1 >= number2; break;
		case TokenType::LESS_OR_EQUALS:    result = number1 <= number2; break;
		case TokenType::EQUALS:            result = fabs(number1 - number2) < DBL_EPSILON; break;
		case TokenType::NOT_EQUALS:        result = fabs(number1 - number2) > DBL_EPSILON; break;
		case TokenType::LOGICAL_AND:       result = (number1 > 0.0) && (number2 > 0.0); break;
		case TokenType::LOGICAL_OR:        result = (number1 > 0.0) || (number2 > 0.0); break;
		default: throw std::runtime_error("Unknown operator");
	}

	return std::make_unique<NumberValue>(result ? 1.0 : 0.0);
}

void ConditionalExpression::accept(IVisitor* visitor) {
	visitor->visit(*this);
}

void ConditionalExpression::innerAccept(IVisitor* visitor) {
	expr1->accept(visitor);
	expr2->accept(visitor);
}