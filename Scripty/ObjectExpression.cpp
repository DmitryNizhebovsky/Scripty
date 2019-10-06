// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "ObjectExpression.h"

ObjectExpression::ObjectExpression(std::map<std::string, std::unique_ptr<IExpression>>&& dictionary) :
    dictionary(std::move(dictionary)) {}

Value ObjectExpression::eval(Scope& scope) {
    std::map<std::string, Value> values;

    for (auto&[key, value] : dictionary) {
        values.insert(std::pair<std::string, Value>(key, value->eval(scope)));
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