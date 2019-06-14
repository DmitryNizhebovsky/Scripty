#pragma once

#include "LangException.h"
#include "IExpression.h"
#include "ObjectValue.h"
#include "InstanceOf.h"
#include "Ilvalue.h"

class ObjectAccessExpression : public IExpression, public Ilvalue {
private:
    std::unique_ptr<IExpression> variable;
    std::string attribute;

private:
    ObjectValue* getObject(Scope& scope) const;

public:
    ObjectAccessExpression(std::unique_ptr<IExpression>&& variable, std::string& attribute);
    virtual std::unique_ptr<IValue> eval(Scope& scope) override;
    virtual std::unique_ptr<IValue>& getRef(Scope& scope) override;
    virtual void accept(IVisitor* visitor) override;
    virtual void innerAccept(IVisitor* visitor) override;
};