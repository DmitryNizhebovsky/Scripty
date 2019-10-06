#pragma once

#include "IExpression.h"
#include "UserFunctionDefine.h"
#include <string>
#include <vector>

class FunctionalExpression : public IExpression {
private:
	std::string name;
	std::vector<std::unique_ptr<IExpression>> args;

public:
	FunctionalExpression(const std::string& name);
	FunctionalExpression(const std::string& name, std::vector<std::unique_ptr<IExpression>>&& args);
	virtual Value eval(Scope& scope) override;
	virtual void accept(IVisitor* visitor) override;
	virtual void innerAccept(IVisitor* visitor) override;
	void addArgument(std::unique_ptr<IExpression>&& arg);
};