#pragma once

#include "IValue.h"
#include "Ilvalue.h"
#include "IExpression.h"

class VariableExpression : public IExpression, public Ilvalue {
private:
	std::string name;

public:
	VariableExpression(const std::string& name);
	virtual Value eval(Scope& scope) override;
	virtual Value& getRef(Scope& scope) override;
	virtual void accept(IVisitor* visitor) override;
	virtual void innerAccept(IVisitor* visitor) override;
};