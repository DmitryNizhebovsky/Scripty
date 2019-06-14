// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "Parser.h"

Parser::Parser(std::vector<Token>& tokens):
	tokens(tokens),
	size(tokens.size()),
	position(0) {}

SPtr Parser::parse() {
	std::unique_ptr<BlockOfStatements> result = std::make_unique<BlockOfStatements>();

	while (!match(TokenType::END_OF_FILE)) {
        SPtr temp = statement();

		if (InstanceOf<FunctionDefineStatement>(temp.get())) {
			result->insertStatement(std::move(temp));
		} else {
			result->addStatement(std::move(temp));
		}
	}

	return result;
}

SPtr Parser::statementOrBlockOfStatements() {
	if (match(TokenType::OPEN_BRACES)) {
		std::unique_ptr<BlockOfStatements> result = std::make_unique<BlockOfStatements>();

		while (!match(TokenType::CLOSE_BRACES)) {
			SPtr temp = statement();

			if (InstanceOf<FunctionDefineStatement>(temp.get())) {
				result->insertStatement(std::move(temp));
			} else {
				result->addStatement(std::move(temp));
			}
		}

		return result;
	} else {
        return statement();
    }
}

SPtr Parser::statement() {
	if (match(TokenType::IF)) {
		return conditionalStatement();
	}

	if (match(TokenType::BREAK)) {
		return breakStatement();
	}

	if (match(TokenType::CONTINUE)) {
		return continueStatement();
	}

	if (match(TokenType::WHILE)) {
		return whileStatement();
	}

	if (match(TokenType::DO_WHILE)) {
		return doWhileStatement();
	}

	if (match(TokenType::FOR)) {
		return forStatement();
	}

	if (match(TokenType::VAR)) {
		return definitionVariableStatement();
	}

	if (lookMatch(TokenType::WORD) && lookMatch(TokenType::OPEN_BRACKET, 1)) {
		return std::make_unique<FunctionStatement>(functionExpressionWithSemicolon());
	}

	if (match(TokenType::FUNCTION)) {
		return definitionFunctionStatement();
	}

	if (match(TokenType::RETURN)) {
        return returnStatement();
	}

	return assignmentStatementWithSemicolon();
}

SPtr Parser::definitionVariableStatement() {
    std::unique_ptr<BlockOfVariableStatements> result = std::make_unique<BlockOfVariableStatements>();
    bool isConst = false;

    if (lookMatch(TokenType::CONST)) {
        consume(TokenType::CONST);
        isConst = true;
    }

    std::string variableName = consume(TokenType::WORD).getValue();

    if (isConst) {
        if (tableOfConstVariable.find(variableName) == tableOfConstVariable.end()) {
            tableOfConstVariable.emplace(variableName);
        } else {
            throw LangException(ExceptionType::ParserError, "Redeclaration of '" + variableName + "'", getPositionBeforeToken(position - 1));
        }
    }

	while (true) {
		if (match(TokenType::ASSIGN)) {
            EPtr expr = expression();

            expressionParsingErrorCheck(expr.get(), "Missing expression");

			result->addStatement(std::make_unique<VariableDefineStatement>(variableName, std::move(expr)));
		} else {
			result->addStatement(std::make_unique<VariableDefineStatement>(variableName, std::make_unique<ValueExpression>(0.0)));
		}

		if (match(TokenType::COMMA)) {
			variableName = consume(TokenType::WORD).getValue();
			continue;
		}

		break;
	}

    consume(TokenType::SEMICOLON);
	return result;
}

SPtr Parser::definitionFunctionStatement() {
	std::string functionName = consume(TokenType::WORD).getValue();
	std::vector<std::string> argsNames;
	consume(TokenType::OPEN_BRACKET);

    if (lookMatch(TokenType::WORD)) {
        do {
            if (lookMatch(TokenType::WORD)) {
                argsNames.emplace_back(consume(TokenType::WORD).getValue());
            } else {
                throw LangException(ExceptionType::ParserError, "Missing argument or )", getPositionAfterToken(position - 1));
            }
        } while (match(TokenType::COMMA));
    }

	consume(TokenType::CLOSE_BRACKET);
	return std::make_unique<FunctionDefineStatement>(functionName, std::move(argsNames), statementOrBlockOfStatements());
}

SPtr Parser::assignmentStatement() {
	std::string variableName = consume(TokenType::WORD).getValue();

    if (tableOfConstVariable.find(variableName) != tableOfConstVariable.end()) {
        throw LangException(ExceptionType::TypeError, "invalid assignment to const '" + variableName + "'");
    }

	std::unique_ptr<BlockOfVariableStatements> result = std::make_unique<BlockOfVariableStatements>();
	EPtr variable;

	while (true) {
		variable = std::make_unique<VariableExpression>(variableName);

		if (lookMatch(TokenType::OPEN_SQUARE_BRACKET)) {
			do {
				consume(TokenType::OPEN_SQUARE_BRACKET);

				EPtr index = expression();

                expressionParsingErrorCheck(index.get(), "Missing expression");

				consume(TokenType::CLOSE_SQUARE_BRACKET);

				variable = std::make_unique<ArrayLikeAccessExpression>(std::move(variable), std::move(index));

			} while (lookMatch(TokenType::OPEN_SQUARE_BRACKET));
		}

        if (lookMatch(TokenType::DOT)) {
            do {
                consume(TokenType::DOT);

                std::string attribute = consume(TokenType::WORD).getValue();

                variable = std::make_unique<ObjectAccessExpression>(std::move(variable), attribute);

            } while (lookMatch(TokenType::DOT));
        }
		
		TokenType assignType = getToken().getType();

		if (assignType == TokenType::ASSIGN           
			|| assignType == TokenType::PLUS_ASSIGN
			|| assignType == TokenType::MINUS_ASSIGN
			|| assignType == TokenType::MULTIPLY_ASSIGN
			|| assignType == TokenType::DIVISION_ASSIGN
			|| assignType == TokenType::MOD_ASSIGN
			|| assignType == TokenType::DIV_ASSIGN)
		{
            consume(assignType);

            EPtr expr = expression();

            expressionParsingErrorCheck(expr.get(), "Missing expression");

			result->addStatement(std::make_unique<AssignmentStatement>(assignType, std::move(variable), std::move(expr)));
		} else {
			throw LangException(ExceptionType::ParserError, "Missing assign expression", getPositionAfterToken(position - 1));
		}

		if (match(TokenType::COMMA)) {
			variableName = consume(TokenType::WORD).getValue();
			continue;
		}

		break;
	}

	return result;
}

SPtr Parser::assignmentStatementWithSemicolon() {
    SPtr statement = assignmentStatement();
    consume(TokenType::SEMICOLON);
    return statement;
}

SPtr Parser::conditionalStatement() {
	EPtr conditional = expression();

    expressionParsingErrorCheck(conditional.get(), "Missing conditional expression");

	SPtr ifStatement = statementOrBlockOfStatements();
	SPtr elseStatement = nullptr;

	if (match(TokenType::ELSE)) {
		elseStatement = statementOrBlockOfStatements();
	}

	return std::make_unique<ConditionalStatement>(std::move(conditional), std::move(ifStatement), std::move(elseStatement));
}

SPtr Parser::whileStatement() {
	EPtr condition = expression();

    expressionParsingErrorCheck(condition.get(), "Missing conditional expression");

	SPtr statement = statementOrBlockOfStatements();
	return std::make_unique<WhileStatement>(std::move(condition), std::move(statement));
}

SPtr Parser::doWhileStatement() {
	SPtr statement = statementOrBlockOfStatements();
    consume(TokenType::WHILE);
	EPtr condition = expression();

    expressionParsingErrorCheck(condition.get(), "Missing conditional expression");

    consume(TokenType::SEMICOLON);
	return std::make_unique<DoWhileStatement>(std::move(condition), std::move(statement));
}

SPtr Parser::forStatement() {
	if (match(TokenType::OPEN_BRACKET)) {
		SPtr initialization;

		if (match(TokenType::VAR)) {
			initialization = definitionVariableStatement();
		} else {
			initialization = assignmentStatement();
		}

		match(TokenType::SEMICOLON);
		EPtr condition = expression();

        expressionParsingErrorCheck(condition.get(), "Missing conditional expression");

		match(TokenType::SEMICOLON);
		SPtr increment = assignmentStatement();

		if (!match(TokenType::CLOSE_BRACKET)) {
            throw LangException(ExceptionType::ParserError, "Missing expression or )", getPositionAfterToken(position - 1));
		}

		SPtr statement = statementOrBlockOfStatements();
		return std::make_unique<ForStatement>(std::move(initialization), std::move(condition), std::move(increment), std::move(statement));
	} else {
		throw LangException(ExceptionType::ParserError, "Missing (", getPositionAfterToken(position - 1));
	}
}

SPtr Parser::continueStatement() {
    SPtr statementTemp = std::make_unique<ContinueStatement>();
    consume(TokenType::SEMICOLON);
    return statementTemp;
}

SPtr Parser::breakStatement() {
    SPtr statementTemp = std::make_unique<BreakStatement>();
    consume(TokenType::SEMICOLON);
    return statementTemp;
}

SPtr Parser::returnStatement() {
    EPtr expr = expression();
    SPtr statementTemp = std::make_unique<ReturnStatement>(std::move(expr));
    consume(TokenType::SEMICOLON);
    return statementTemp;
}

EPtr Parser::arrayExpression() {
	std::vector<EPtr> expressions;
    EPtr expr = nullptr;

    consume(TokenType::OPEN_SQUARE_BRACKET);

    if (!lookMatch(TokenType::CLOSE_SQUARE_BRACKET)) {
        do {
            expr = expression();

            expressionParsingErrorCheck(expr.get(), "Missing expression or ]");

            expressions.emplace_back(std::move(expr));

        } while (match(TokenType::COMMA));
    }

    consume(TokenType::CLOSE_SQUARE_BRACKET);
	return std::make_unique<ArrayExpression>(std::move(expressions));
}

EPtr Parser::objectExpression() {
    std::map<std::string, EPtr> dictionary;

    consume(TokenType::OPEN_BRACES);

    if (!lookMatch(TokenType::CLOSE_BRACES)) {
        do {
            std::string attribute = consume(TokenType::WORD).getValue();

            consume(TokenType::COLON);

            EPtr expr = expression();

            expressionParsingErrorCheck(expr.get(), "Missing expression");

            dictionary.insert(std::pair<std::string, EPtr>(attribute, std::move(expr)));

        } while (match(TokenType::COMMA));
    }

    consume(TokenType::CLOSE_BRACES);
    return std::make_unique<ObjectExpression>(std::move(dictionary));
}

EPtr Parser::objectItemAccessExpression() {
    std::string variableName = consume(TokenType::WORD).getValue();
    EPtr variable = std::make_unique<VariableExpression>(variableName);

    do {
        consume(TokenType::DOT);

        std::string attribute = consume(TokenType::WORD).getValue();

        variable = std::make_unique<ObjectAccessExpression>(std::move(variable), attribute);

    } while (lookMatch(TokenType::DOT));

    return variable;
}

EPtr Parser::arrayItemAccessExpression() {
	std::string variableName = consume(TokenType::WORD).getValue();
	EPtr variable = std::make_unique<VariableExpression>(variableName);

	do {
		consume(TokenType::OPEN_SQUARE_BRACKET);

		EPtr index = expression();

        expressionParsingErrorCheck(index.get(), "Missing expression");

		consume(TokenType::CLOSE_SQUARE_BRACKET);

		variable = std::make_unique<ArrayLikeAccessExpression>(std::move(variable), std::move(index));
	} while (lookMatch(TokenType::OPEN_SQUARE_BRACKET));
	
	return variable;
}

EPtr Parser::functionExpression() {
	std::string name = consume(TokenType::WORD).getValue();
	std::unique_ptr<FunctionalExpression> function = std::make_unique<FunctionalExpression>(name);
    EPtr expr = nullptr;

	consume(TokenType::OPEN_BRACKET);

    if (!lookMatch(TokenType::CLOSE_BRACKET)) {
        do {
            expr = expression();

            expressionParsingErrorCheck(expr.get(), "Missing expression or )");

            function->addArgument(std::move(expr));

        } while (match(TokenType::COMMA));
    }

	consume(TokenType::CLOSE_BRACKET);
	return function;
}

EPtr Parser::functionExpressionWithSemicolon() {
    EPtr function = functionExpression();
    consume(TokenType::SEMICOLON);
    return function;
}

EPtr Parser::expression() {
	return logicaOr();
}

EPtr Parser::subExpression() {
    EPtr result = expression();

    expressionParsingErrorCheck(result.get(), "Missing expression");

    if (!match(TokenType::CLOSE_BRACKET)) {
        throw LangException(ExceptionType::ParserError, "Missing )", getPositionAfterToken(position - 1));
    }

    return result;
}

EPtr Parser::logicaOr() {
	EPtr result = logicalAnd();

	while (true) {
		if (match(TokenType::LOGICAL_OR)) {
			result = std::make_unique<ConditionalExpression>(TokenType::LOGICAL_OR, std::move(result), logicalAnd());
			continue;
		}

		break;
	}

	return result;
}

EPtr Parser::logicalAnd() {
	EPtr result = equality();

	while (true) {
		if (match(TokenType::LOGICAL_AND)) {
			result = std::make_unique<ConditionalExpression>(TokenType::LOGICAL_AND, std::move(result), equality());
			continue;
		}

		break;
	}

	return result;
}

EPtr Parser::equality() {
	EPtr result = conditional();

	while (true) {
		if (match(TokenType::EQUALS)) {
			result = std::make_unique<ConditionalExpression>(TokenType::EQUALS, std::move(result), conditional());
			continue;
		}

		if (match(TokenType::NOT_EQUALS)) {
			result = std::make_unique<ConditionalExpression>(TokenType::NOT_EQUALS, std::move(result), conditional());
			continue;
		}

		break;
	}

	return result;
}

EPtr Parser::conditional() {
	EPtr result = additive();

	while (true) {
		if (match(TokenType::GREATER_THAN)) {
			result = std::make_unique<ConditionalExpression>(TokenType::GREATER_THAN, std::move(result), additive());
			continue;
		}

		if (match(TokenType::GREATER_OR_EQUALS)) {
			result = std::make_unique<ConditionalExpression>(TokenType::GREATER_OR_EQUALS, std::move(result), additive());
			continue;
		}

		if (match(TokenType::LESS_THAN)) {
			result = std::make_unique<ConditionalExpression>(TokenType::LESS_THAN, std::move(result), additive());
			continue;
		}

		if (match(TokenType::LESS_OR_EQUALS)) {
			result = std::make_unique<ConditionalExpression>(TokenType::LESS_OR_EQUALS, std::move(result), additive());
			continue;
		}

		break;
	}

	return result;
}

EPtr Parser::additive() {
	EPtr result = multiplicative();

	while (true) {
		if (match(TokenType::PLUS)) {
			result = std::make_unique<BinaryExpression>(TokenType::PLUS, std::move(result), multiplicative());
			continue;
		}

		if (match(TokenType::MINUS)) {
			result = std::make_unique<BinaryExpression>(TokenType::MINUS, std::move(result), multiplicative());
			continue;
		}

		break;
	}

	return result;
}

EPtr Parser::multiplicative() {
	EPtr result = unary();

	while (true) {
		if (match(TokenType::MULTIPLY)) {
			result = std::make_unique<BinaryExpression>(TokenType::MULTIPLY, std::move(result), unary());
			continue;
		}

		if (match(TokenType::DIVISION)) {
			result = std::make_unique<BinaryExpression>(TokenType::DIVISION, std::move(result), unary());
			continue;
		}

		if (match(TokenType::MOD)) {
			result = std::make_unique<BinaryExpression>(TokenType::MOD, std::move(result), unary());
			continue;
		}

		if (match(TokenType::DIV)) {
			result = std::make_unique<BinaryExpression>(TokenType::DIV, std::move(result), unary());
			continue;
		}

		break;
	}

	return result;
}

EPtr Parser::unary() {
	if (match(TokenType::MINUS)) {
		return std::make_unique<UnaryExpression>(TokenType::MINUS, primary());
	}

	if (match(TokenType::PLUS)) {
		return std::make_unique<UnaryExpression>(TokenType::PLUS, primary());
	}

	if (match(TokenType::LOGICAL_NOT)) {
		return std::make_unique<UnaryExpression>(TokenType::LOGICAL_NOT, primary());
	}

	return primary();
}

EPtr Parser::primary() {
    const Token& token = getToken();

	if (match(TokenType::NUMBER)) {
		return std::make_unique<ValueExpression>(std::stod(token.getValue()));
	}

	if (match(TokenType::STRING)) {
		return std::make_unique<ValueExpression>(token.getValue());
	}

	if (match(TokenType::FALSE)) {
		return std::make_unique<ValueExpression>(0.0);
	}

	if (match(TokenType::TRUE)) {
		return std::make_unique<ValueExpression>(1.0);
	}

	if (lookMatch(TokenType::WORD) && lookMatch(TokenType::OPEN_BRACKET, 1)) {
		return functionExpression();
	}

	if (lookMatch(TokenType::WORD) && lookMatch(TokenType::OPEN_SQUARE_BRACKET, 1)) {
		return arrayItemAccessExpression();
	}

    if (lookMatch(TokenType::WORD) && lookMatch(TokenType::DOT, 1)) {
        return objectItemAccessExpression();
    }

	if (match(TokenType::WORD)) {
		return std::make_unique<VariableExpression>(token.getValue());
	}

	if (lookMatch(TokenType::OPEN_SQUARE_BRACKET)) {
		return arrayExpression();
	}

    if (lookMatch(TokenType::OPEN_BRACES)) {
        return objectExpression();
    }

	if (match(TokenType::OPEN_BRACKET)) {
		return subExpression();
	}

    return nullptr;
}

const Token& Parser::getToken(const size_t relativePos) const {
	size_t pos = position + relativePos;

	if (pos >= size) {
		return Token(TokenType::END_OF_FILE);
	}

	return tokens[pos];
}

const Token& Parser::consume(const TokenType type) {
	if (type == getToken().getType()) {
		return tokens[position++];
	}

    throw LangException(ExceptionType::ParserError, "Missing " + tokenTypeToString(type), getPositionAfterToken(position - 1));
}

const bool Parser::lookMatch(const TokenType type, const size_t pos) const {
	return getToken(pos).getType() == type;
}

const bool Parser::match(const TokenType type) {
	if (type != getToken().getType()) {
		return false;
	}

	position++;
	return true;
}

const TokenPosition Parser::getPositionAfterToken(const size_t pos) const {
    const Token& token = tokens[pos];
    const TokenPosition& tokenPos = token.getPosition();
    return TokenPosition(tokenPos.row, tokenPos.column + token.getValue().length());
}

const TokenPosition Parser::getPositionBeforeToken(const size_t pos) const {
    const Token& token = tokens[pos];

    if (pos == 0 || token.getPosition().column > 1) {
        return token.getPosition();
    }
    else {
        return getPositionAfterToken(pos - 1);
    }
}

const void Parser::expressionParsingErrorCheck(const IExpression* expression, const std::string& errorMsg) const {
    if (expression == nullptr) {
        throw LangException(ExceptionType::ParserError, errorMsg, getPositionAfterToken(position - 1));
    }
}