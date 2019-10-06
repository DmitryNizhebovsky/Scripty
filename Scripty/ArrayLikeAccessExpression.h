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
    ICollection* getCollectionPtr(Scope& scope);

public:
	ArrayLikeAccessExpression(std::unique_ptr<IExpression>&& variable, std::unique_ptr<IExpression>&& index);
	virtual Value eval(Scope& scope) override;
	virtual Value& getRef(Scope& scope) override;
	virtual void accept(IVisitor* visitor) override;
	virtual void innerAccept(IVisitor* visitor) override;
};