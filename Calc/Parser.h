#pragma once

#include "Token.h"
#include "LangException.h"

#include "BlockOfVariableStatements.h"
#include "FunctionDefineStatement.h"
#include "VariableDefineStatement.h"
#include "ConditionalStatement.h"
#include "AssignmentStatement.h"
#include "FunctionStatement.h"
#include "ContinueStatement.h"
#include "BlockOfStatements.h"
#include "DoWhileStatement.h"
#include "ReturnStatement.h"
#include "BreakStatement.h"
#include "WhileStatement.h"
#include "ForStatement.h"

#include "ArrayLikeAccessExpression.h"
#include "ConditionalExpression.h"
#include "FunctionalExpression.h"
#include "VariableExpression.h"
#include "BinaryExpression.h"
#include "ValueExpression.h"
#include "UnaryExpression.h"
#include "ArrayExpression.h"
#include "ObjectExpression.h"

#include <set>

using SPtr = std::unique_ptr<IStatement>;
using EPtr = std::unique_ptr<IExpression>;

class Parser {
private:
	std::vector<Token> tokens;
    std::set<std::string> tableOfConstVariable;

	size_t position;
	size_t size;

    Token eof;

private:
    const Token& getToken(const size_t relativePos = 0) const;
    const Token& consume(const TokenType type);
    const bool match(const TokenType type);
	const bool lookMatch(const TokenType type, const size_t pos = 0) const;

    const void expressionParsingErrorCheck(const IExpression* expression, const std::string& errorMsg) const;

    const TokenPosition getPositionAfterToken(const size_t pos) const;
    const TokenPosition getPositionBeforeToken(const size_t pos) const;
	
    SPtr statementOrBlockOfStatements();
    SPtr definitionVariableStatement();
    SPtr definitionFunctionStatement();
    SPtr conditionalStatement();
    SPtr assignmentStatement();
    SPtr assignmentStatementWithSemicolon();
    SPtr continueStatement();
    SPtr doWhileStatement();
    SPtr returnStatement();
    SPtr whileStatement();
    SPtr breakStatement();
    SPtr forStatement();
    SPtr statement();

    EPtr arrayItemAccessExpression();
    EPtr objectItemAccessExpression();
    EPtr functionExpression();
    EPtr functionExpressionWithSemicolon();
    EPtr objectExpression();
    EPtr arrayExpression();
    EPtr multiplicative();
    EPtr subExpression();
    EPtr conditional();
    EPtr expression();
    EPtr logicalAnd();
    EPtr additive();
    EPtr logicaOr();
    EPtr equality();
    EPtr primary();
    EPtr unary();

public:
	Parser();
    SPtr parse(std::vector<Token>&& tokensArray);
};