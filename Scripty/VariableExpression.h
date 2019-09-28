#pragma once

#include "IValue.h"
#include "Ilvalue.h"
#include "IExpression.h"

class VariableExpression : public IExpression, public Ilvalue {
private:
	std::string name;

public:
	VariableExpression(const std::string& name);
	virtual std::unique_ptr<IValue> eval(Scope& scope) override;
	virtual std::unique_ptr<IValue>& getRef(Scope& scope) override;
	virtual void accept(IVisitor* visitor) override;
	virtual void innerAccept(IVisitor* visitor) override;
};