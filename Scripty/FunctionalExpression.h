#pragma once

#include "IExpression.h"
#include <string>
#include <vector>

class FunctionalExpression : public IExpression {
private:
	std::string name;
	std::vector<std::unique_ptr<IExpression>> args;

public:
	FunctionalExpression(const std::string& name, std::vector<std::unique_ptr<IExpression>>&& args);

	virtual Value eval(Scope& scope) override;

    virtual void accept(IVisitor* visitor) override;
    virtual void innerAccept(IVisitor* visitor) override;

private:
    void checkNumberArgumentsPassed(size_t argsCountExpected, size_t argsCountPassed, IFunction* function, bool checkMax = false) const;
};