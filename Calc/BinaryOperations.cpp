#include "BinaryOperations.h"

std::unique_ptr<IValue> binaryAdd(std::unique_ptr<IExpression>& expr1, std::unique_ptr<IExpression>& expr2, Scope& scope) {
	std::unique_ptr<IValue> value1 = expr1->eval(scope);
	std::unique_ptr<IValue> value2 = expr2->eval(scope);

	if (InstanceOf<NumberValue>(value1.get()) && InstanceOf<NumberValue>(value2.get())) {
		return std::make_unique<NumberValue>(value1->asDouble() + value2->asDouble());
	}

	if (InstanceOf<StringValue>(value1.get()) || InstanceOf<StringValue>(value2.get())) {
		return std::make_unique<StringValue>(value1->asString() + value2->asString());
	}

	throw std::runtime_error("Unable to perform operation on these types");
}

std::unique_ptr<IValue> binarySub(std::unique_ptr<IExpression>& expr1, std::unique_ptr<IExpression>& expr2, Scope& scope) {
	std::unique_ptr<IValue> value1 = expr1->eval(scope);
	std::unique_ptr<IValue> value2 = expr2->eval(scope);

	if (InstanceOf<NumberValue>(value1.get()) && InstanceOf<NumberValue>(value2.get())) {
		return std::make_unique<NumberValue>(value1->asDouble() - value2->asDouble());
	}

	throw std::runtime_error("Unable to perform operation on these types");
}

std::unique_ptr<IValue> binaryMul(std::unique_ptr<IExpression>& expr1, std::unique_ptr<IExpression>& expr2, Scope& scope) {
	std::unique_ptr<IValue> value1 = expr1->eval(scope);
	std::unique_ptr<IValue> value2 = expr2->eval(scope);

	if (InstanceOf<NumberValue>(value1.get()) && InstanceOf<NumberValue>(value2.get())) {
		return std::make_unique<NumberValue>(value1->asDouble() * value2->asDouble());
	}

	if ((InstanceOf<StringValue>(value1.get()) && InstanceOf<NumberValue>(value2.get())) || 
		(InstanceOf<NumberValue>(value1.get()) && InstanceOf<StringValue>(value2.get()))) {
		int count = 0;
		std::string buffer = "";
		std::string pattern = "";

		if (InstanceOf<NumberValue>(value2.get())) {
			count = static_cast<int>(value2->asDouble());
			pattern = value1->asString();
		}
		else {
			count = static_cast<int>(value1->asDouble());
			pattern = value2->asString();
		}

		for (int i = 0; i < count; ++i) {
			buffer += pattern;
		}

		return std::make_unique<StringValue>(buffer);
	}

	throw std::runtime_error("Unable to perform operation on these types");
}

std::unique_ptr<IValue> binaryDiv(std::unique_ptr<IExpression>& expr1, std::unique_ptr<IExpression>& expr2, Scope& scope) {
	std::unique_ptr<IValue> value1 = expr1->eval(scope);
	std::unique_ptr<IValue> value2 = expr2->eval(scope);

	if (InstanceOf<NumberValue>(value1.get()) && InstanceOf<NumberValue>(value2.get())) {
		return std::make_unique<NumberValue>(value1->asDouble() / value2->asDouble());
	}

	throw std::runtime_error("Unable to perform operation on these types");
}

std::unique_ptr<IValue> binaryMod(std::unique_ptr<IExpression>& expr1, std::unique_ptr<IExpression>& expr2, Scope& scope) {
	std::unique_ptr<IValue> value1 = expr1->eval(scope);
	std::unique_ptr<IValue> value2 = expr2->eval(scope);

	if (InstanceOf<NumberValue>(value1.get()) && InstanceOf<NumberValue>(value2.get())) {
		return std::make_unique<NumberValue>(static_cast<double>(static_cast<int>(value1->asDouble()) % static_cast<int>(value2->asDouble())));
	}

	throw std::runtime_error("Unable to perform operation on these types");
}

std::unique_ptr<IValue> binaryIntDiv(std::unique_ptr<IExpression>& expr1, std::unique_ptr<IExpression>& expr2, Scope& scope) {
	std::unique_ptr<IValue> value1 = expr1->eval(scope);
	std::unique_ptr<IValue> value2 = expr2->eval(scope);

	if (InstanceOf<NumberValue>(value1.get()) && InstanceOf<NumberValue>(value2.get())) {
		return std::make_unique<NumberValue>(static_cast<double>(static_cast<int>(value1->asDouble()) / static_cast<int>(value2->asDouble())));
	}

	throw std::runtime_error("Unable to perform operation on these types");
}