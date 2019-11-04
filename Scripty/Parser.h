#pragma once

#include "Token.h"
#include "LangException.h"

#include "BlockOfVariableStatements.h"
#include "FunctionDefinitionStatement.h"
#include "VariableDefinitionStatement.h"
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
#include "FunctionExpression.h"
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
    std::set<std::string> tableOfConstantVariables;

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

    // Parsing statements
	
    SPtr parseStatement();
    SPtr parseStatementOrBlockOfStatements();

    SPtr parseVariableDefinitionStatement();
    SPtr parseFunctionDefinitionStatement();

    SPtr parseConditionalStatement();

    SPtr parseAssignmentStatement();
    SPtr parseAssignmentStatementWithSemicolon();

    SPtr parseContinueStatement();
    SPtr parseReturnStatement();
    SPtr parseBreakStatement();

    SPtr parseDoWhileStatement();
    SPtr parseWhileStatement();
    SPtr parseForStatement();

    // Parsing expressions

    EPtr parseArrayExpression();
    EPtr parseArrayItemAccessExpression();

    EPtr parseObjectExpression();
    EPtr parseObjectItemAccessExpression();

    EPtr parseFunctionExpression();
    EPtr parseFunctionExpressionWithSemicolon();
    
    EPtr parseMultiplicativeExpression();
    EPtr parseAdditiveExpression();
    EPtr parsePrimaryExpression();
    EPtr parseUnaryExpression();

    EPtr parseExpression();
    EPtr parseSubExpression();

    EPtr parseConditionalExpression();
    EPtr parseLogicalAndExpression();
    EPtr parseLogicaOrExpression();
    EPtr parseEqualityExpression();

public:
	Parser();
    SPtr parse(std::vector<Token>&& tokensArray);
};