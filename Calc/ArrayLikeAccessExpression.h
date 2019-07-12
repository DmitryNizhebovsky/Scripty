#pragma once

#include "LangException.h"
#include "IExpression.h"
#include "ArrayValue.h"
#include "ObjectValue.h"
#include "StringValue.h"
#include "InstanceOf.h"
#include "Ilvalue.h"

class ArrayLikeAccessExpression : public IExpression, public Ilvalue {
private:
	std::unique_ptr<IExpression> variable;
	std::unique_ptr<IExpression> index;

private:
    std::unique_ptr<IValue>& getVariableRef(Scope& scope) const;

public:
	ArrayLikeAccessExpression(std::unique_ptr<IExpression>&& variable, std::unique_ptr<IExpression>&& index);
	virtual std::unique_ptr<IValue> eval(Scope& scope) override;
	virtual std::unique_ptr<IValue>& getRef(Scope& scope) override;
	virtual void accept(IVisitor* visitor) override;
	virtual void innerAccept(IVisitor* visitor) override;
};