#include "ArrayLikeAccessExpression.h"

ArrayLikeAccessExpression::ArrayLikeAccessExpression(std::unique_ptr<IExpression>&& variable, std::unique_ptr<IExpression>&& index) :
	variable(std::move(variable)),
	index(std::move(index)) {}

std::unique_ptr<IValue>& ArrayLikeAccessExpression::getVariableRef(Scope& scope) const {
    Ilvalue* variablePtr = dynamic_cast<Ilvalue*>(variable.get());

    if (variablePtr == nullptr) {
        throw LangException(ExceptionType::RuntimeError, "Unable to assign value to left expression");
    }

    return variablePtr->getRef(scope);
}

std::unique_ptr<IValue> ArrayLikeAccessExpression::eval(Scope& scope) {
    ArrayValue* array = dynamic_cast<ArrayValue*>(getVariableRef(scope).get());

    if (array) {
        int indexVal = static_cast<int>(index->eval(scope)->asDouble());
        return array->getValue(indexVal);
    }
    else {
        ObjectValue* object = dynamic_cast<ObjectValue*>(getVariableRef(scope).get());

        if (object) {
            std::string attribute = index->eval(scope)->asString();
            return object->getValue(attribute);
        }
        else {
            throw LangException(ExceptionType::RuntimeError, "[...] can only be used with arrays or objects");
        }
    }
}

std::unique_ptr<IValue>& ArrayLikeAccessExpression::getRef(Scope& scope) {
    ArrayValue* array = dynamic_cast<ArrayValue*>(getVariableRef(scope).get());

    if (array) {
        int indexVal = static_cast<int>(index->eval(scope)->asDouble());
        return array->getValueRef(indexVal);
    }
    else {
        ObjectValue* object = dynamic_cast<ObjectValue*>(getVariableRef(scope).get());

        if (object) {
            std::string attribute = index->eval(scope)->asString();
            return object->getValueRef(attribute);
        }
        else {
            throw LangException(ExceptionType::RuntimeError, "[...] can only be used with arrays or objects");
        }
    }
}

void ArrayLikeAccessExpression::accept(IVisitor* visitor) {
	visitor->visit(*this);
}

void ArrayLikeAccessExpression::innerAccept(IVisitor* visitor) {
	variable->accept(visitor);
	index->accept(visitor);
}