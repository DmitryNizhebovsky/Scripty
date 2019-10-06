#pragma once

#include "IExpression.h"
#include "ObjectValue.h"
#include <map>

class ObjectExpression : public IExpression {
private:
    std::map<std::string, std::unique_ptr<IExpression>> dictionary;

public:
    ObjectExpression(std::map<std::string, std::unique_ptr<IExpression>>&& dictionary);
    virtual Value eval(Scope& scope) override;
    virtual void accept(IVisitor* visitor) override;
    virtual void innerAccept(IVisitor* visitor) override;
};