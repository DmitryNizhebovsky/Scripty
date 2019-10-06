// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "ArrayLikeAccessExpression.h"

ArrayLikeAccessExpression::ArrayLikeAccessExpression(std::unique_ptr<IExpression>&& variable, std::unique_ptr<IExpression>&& index) :
	variable(std::move(variable)),
	index(std::move(index)) {}

ICollection* ArrayLikeAccessExpression::getCollectionPtr(Scope& scope) {
    Ilvalue* variablePtr = dynamic_cast<Ilvalue*>(variable.get());

    if (variablePtr == nullptr) {
        throw LangException(ExceptionType::RuntimeError, "Unable to assign value to left expression");
    }

    Value& valueRef = variablePtr->getRef(scope);
    ICollection* collection = dynamic_cast<ICollection*>(valueRef.get());

    if (!collection) {
        throw LangException(ExceptionType::RuntimeError, "[...] can only be used with arrays, objects or strings");
    }

    return collection;
}

Value ArrayLikeAccessExpression::eval(Scope& scope) {
    ICollection* collection = getCollectionPtr(scope);

    return collection->getValue(std::move(index->eval(scope)));
}

Value& ArrayLikeAccessExpression::getRef(Scope& scope) {
    ICollection* collection = getCollectionPtr(scope);

    return collection->getValueRef(std::move(index->eval(scope)));
}

void ArrayLikeAccessExpression::accept(IVisitor* visitor) {
	visitor->visit(*this);
}

void ArrayLikeAccessExpression::innerAccept(IVisitor* visitor) {
	variable->accept(visitor);
	index->accept(visitor);
}