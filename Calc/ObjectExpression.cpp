#include "ObjectExpression.h"

ObjectExpression::ObjectExpression(std::map<std::string, std::unique_ptr<IExpression>>&& dictionary) :
    dictionary(std::move(dictionary)) {}

std::unique_ptr<IValue> ObjectExpression::eval(Scope& scope) {
    std::map<std::string, std::unique_ptr<IValue>> values;

    for (auto&[key, value] : dictionary) {
        values.insert(std::pair<std::string, std::unique_ptr<IValue>>(key, value->eval(scope)));
    }

    return std::make_unique<ObjectValue>(std::move(values));
}

void ObjectExpression::accept(IVisitor* visitor) {
    visitor->visit(*this);
}

void ObjectExpression::innerAccept(IVisitor* visitor) {
    for (auto& item : dictionary) {
        item.second->accept(visitor);
    }
}