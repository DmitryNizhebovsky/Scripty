#include "ObjectAccessExpression.h"

ObjectAccessExpression::ObjectAccessExpression(std::unique_ptr<IExpression>&& variable, std::string& attribute): 
    variable(std::move(variable)),
    attribute(attribute) {}

ObjectValue* ObjectAccessExpression::getObject(Scope& scope) const {
    Ilvalue* variablePtr = dynamic_cast<Ilvalue*>(variable.get());

    if (variablePtr == nullptr) {
        throw LangException(ExceptionType::RuntimeError, "Unable to assign value to left expression");
    }

    std::unique_ptr<IValue>& objectRef = variablePtr->getRef(scope);
    ObjectValue* object = dynamic_cast<ObjectValue*>(objectRef.get());

    if (object == nullptr) {
        throw LangException(ExceptionType::RuntimeError, "Missing object value");
    }

    return object;
}

std::unique_ptr<IValue> ObjectAccessExpression::eval(Scope& scope) {
    ObjectValue* object = getObject(scope);

    return object->getValue(attribute);
}

std::unique_ptr<IValue>& ObjectAccessExpression::getRef(Scope& scope) {
    ObjectValue* object = getObject(scope);

    return object->getValueRef(attribute);
}

void ObjectAccessExpression::accept(IVisitor* visitor) {
    visitor->visit(*this);
}

void ObjectAccessExpression::innerAccept(IVisitor* visitor) {
    variable->accept(visitor);
}