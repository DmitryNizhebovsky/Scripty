#pragma once

#include "IValue.h"
#include "IExpression.h"
#include "Scope.h"
#include <memory>

std::unique_ptr<IValue> binaryAdd(std::unique_ptr<IExpression>& expr1, std::unique_ptr<IExpression>& expr2, Scope& scope);
std::unique_ptr<IValue> binarySub(std::unique_ptr<IExpression>& expr1, std::unique_ptr<IExpression>& expr2, Scope& scope);
std::unique_ptr<IValue> binaryMul(std::unique_ptr<IExpression>& expr1, std::unique_ptr<IExpression>& expr2, Scope& scope);
std::unique_ptr<IValue> binaryDiv(std::unique_ptr<IExpression>& expr1, std::unique_ptr<IExpression>& expr2, Scope& scope);
std::unique_ptr<IValue> binaryMod(std::unique_ptr<IExpression>& expr1, std::unique_ptr<IExpression>& expr2, Scope& scope);
std::unique_ptr<IValue> binaryIntDiv(std::unique_ptr<IExpression>& expr1, std::unique_ptr<IExpression>& expr2, Scope& scope);