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
#include "ObjectAccessExpression.h"
#include "ConditionalExpression.h"
#include "FunctionalExpression.h"
#include "VariableExpression.h"
#include "BinaryExpression.h"
#include "ValueExpression.h"
#include "UnaryExpression.h"
#include "ArrayExpression.h"
#include "ObjectExpression.h"

#include <set>

class Parser {
private:
	std::vector<Token> tokens;
    std::set<std::string> tableOfConstVariable;
	Token eof;
	size_t position;
	size_t size;

private:
    const Token& getToken(const size_t relativePos = 0) const;
    const Token& consume(const TokenType type);
    const bool match(const TokenType type);
	const bool lookMatch(const TokenType type, const size_t pos = 0) const;

    const void expressionParsingErrorCheck(const IExpression* expression, const std::string errorMsg) const;

    const TokenPosition getPositionAfterToken(const size_t pos) const;
    const TokenPosition getPositionBeforeToken(const size_t pos) const;
	
	std::unique_ptr<IStatement> statementOrBlockOfStatements();
	std::unique_ptr<IStatement> definitionVariableStatement();
	std::unique_ptr<IStatement> definitionFunctionStatement();
	std::unique_ptr<IStatement> conditionalStatement();
	std::unique_ptr<IStatement> assignmentStatement();
    std::unique_ptr<IStatement> assignmentStatementWithSemicolon();
    std::unique_ptr<IStatement> continueStatement();
	std::unique_ptr<IStatement> doWhileStatement();
    std::unique_ptr<IStatement> returnStatement();
	std::unique_ptr<IStatement> whileStatement();
    std::unique_ptr<IStatement> breakStatement();
	std::unique_ptr<IStatement> forStatement();
	std::unique_ptr<IStatement> statement();

	std::unique_ptr<IExpression> arrayItemAccessExpression();
    std::unique_ptr<IExpression> objectItemAccessExpression();
	std::unique_ptr<IExpression> functionExpression();
    std::unique_ptr<IExpression> functionExpressionWithSemicolon();
    std::unique_ptr<IExpression> objectExpression();
	std::unique_ptr<IExpression> arrayExpression();
	std::unique_ptr<IExpression> multiplicative();
	std::unique_ptr<IExpression> subExpression();
	std::unique_ptr<IExpression> conditional();
	std::unique_ptr<IExpression> expression();
	std::unique_ptr<IExpression> logicalAnd();
	std::unique_ptr<IExpression> additive();
	std::unique_ptr<IExpression> logicaOr();
	std::unique_ptr<IExpression> equality();
	std::unique_ptr<IExpression> primary();
    std::unique_ptr<IExpression> unary();

public:
	Parser(std::vector<Token>& tokens);
	std::unique_ptr<IStatement> parse();
};