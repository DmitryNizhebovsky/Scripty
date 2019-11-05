// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "Parser.h"

Parser::Parser():
    size(0),
    position(0),
    eof(TokenType::END_OF_FILE) {}

SPtr Parser::parse(const std::vector<Token>& tokensArray) {
    tokens = tokensArray;
    size = tokens.size();

	std::unique_ptr<BlockOfStatements> result = std::make_unique<BlockOfStatements>();

	while (!match(TokenType::END_OF_FILE)) {
        SPtr temp = parseStatement();

		if (InstanceOf<FunctionDefinitionStatement>(temp.get())) {
			result->insertStatement(std::move(temp));
		} else {
			result->addStatement(std::move(temp));
		}
	}

	return result;
}

SPtr Parser::parseStatementOrBlockOfStatements() {
	if (match(TokenType::OPEN_BRACES)) {
		std::unique_ptr<BlockOfStatements> result = std::make_unique<BlockOfStatements>();

		while (!match(TokenType::CLOSE_BRACES)) {
			SPtr temp = parseStatement();

			if (InstanceOf<FunctionDefinitionStatement>(temp.get())) {
				result->insertStatement(std::move(temp));
			} else {
				result->addStatement(std::move(temp));
			}
		}

		return result;
	} else {
        return parseStatement();
    }
}

SPtr Parser::parseStatement() {
	if (match(TokenType::IF)) {
		return parseConditionalStatement();
	}

	if (match(TokenType::BREAK)) {
		return parseBreakStatement();
	}

	if (match(TokenType::CONTINUE)) {
		return parseContinueStatement();
	}

	if (match(TokenType::WHILE)) {
		return parseWhileStatement();
	}

	if (match(TokenType::DO_WHILE)) {
		return parseDoWhileStatement();
	}

	if (match(TokenType::FOR)) {
		return parseForStatement();
	}

	if (match(TokenType::VAR)) {
		return parseVariableDefinitionStatement();
	}

	if (lookMatch(TokenType::WORD) && lookMatch(TokenType::OPEN_BRACKET, 1)) {
		return std::make_unique<FunctionStatement>(parseFunctionExpressionWithSemicolon());
	}

	if (match(TokenType::FUNCTION)) {
		return parseFunctionDefinitionStatement();
	}

	if (match(TokenType::RETURN)) {
        return parseReturnStatement();
	}

	return parseAssignmentStatementWithSemicolon();
}

SPtr Parser::parseVariableDefinitionStatement() {
    std::unique_ptr<BlockOfVariableStatements> result = std::make_unique<BlockOfVariableStatements>();
    //bool isConst = false;

    if (lookMatch(TokenType::CONST)) {
        consume(TokenType::CONST);
        //isConst = true;
    }

    std::string variableName = consume(TokenType::WORD).getValue();

    //if (isConst) {
    //    if (tableOfConstantVariables.find(variableName) == tableOfConstantVariables.end()) {
    //        tableOfConstantVariables.emplace(variableName);
    //    } else {
    //        throw LangException(ExceptionType::ParserError, "Redeclaration of '" + variableName + "'", getPositionBeforeToken(position - 1));
    //    }
    //}

	while (true) {
		if (match(TokenType::ASSIGN)) {
            EPtr expr = parseExpression();

            expressionParsingErrorCheck(expr.get(), "Missing expression");

			result->addStatement(std::make_unique<VariableDefinitionStatement>(variableName, std::move(expr)));
		} else {
			result->addStatement(std::make_unique<VariableDefinitionStatement>(variableName, std::make_unique<ValueExpression>(0.0)));
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

SPtr Parser::parseFunctionDefinitionStatement() {
	std::string functionName = consume(TokenType::WORD).getValue();
	std::vector<std::string> args;
	consume(TokenType::OPEN_BRACKET);

    if (lookMatch(TokenType::WORD)) {
        do {
            if (lookMatch(TokenType::WORD)) {
                args.emplace_back(consume(TokenType::WORD).getValue());
            } else {
                throw LangException(ExceptionType::ParserError, "Missing argument or )", getPositionAfterToken(position - 1));
            }
        } while (match(TokenType::COMMA));
    }

	consume(TokenType::CLOSE_BRACKET);
	return std::make_unique<FunctionDefinitionStatement>(functionName, std::move(args), parseStatementOrBlockOfStatements(), true);
}

SPtr Parser::parseAssignmentStatement() {
	std::unique_ptr<BlockOfVariableStatements> result = std::make_unique<BlockOfVariableStatements>();
	EPtr variable = nullptr;

	do {
        if (lookMatch(TokenType::WORD) && lookMatch(TokenType::OPEN_SQUARE_BRACKET, 1)) {
            variable = parseArrayLikeAccessExpression();
        }
        else if (lookMatch(TokenType::WORD) && lookMatch(TokenType::DOT, 1)) {
            variable = parseObjectLikeAccessExpression();
        }
        else {
            std::string variableName = consume(TokenType::WORD).getValue();
            variable = std::make_unique<VariableExpression>(variableName);
        }
		
		TokenType assignType = getToken().getType();

		if (Token::isAssignmentOperator(assignType))
		{
            consume(assignType);

            EPtr expr = parseExpression();

            expressionParsingErrorCheck(expr.get(), "Missing expression");

			result->addStatement(std::make_unique<AssignmentStatement>(assignType, std::move(variable), std::move(expr)));
		} else {
			throw LangException(ExceptionType::ParserError, "Missing assign expression", getPositionAfterToken(position - 1));
		}
    } while(match(TokenType::COMMA));

	return result;
}

SPtr Parser::parseAssignmentStatementWithSemicolon() {
    SPtr statement = parseAssignmentStatement();
    consume(TokenType::SEMICOLON);
    return statement;
}

SPtr Parser::parseConditionalStatement() {
	EPtr conditional = parseExpression();

    expressionParsingErrorCheck(conditional.get(), "Missing conditional expression");

	SPtr ifStatement = parseStatementOrBlockOfStatements();
	SPtr elseStatement = nullptr;

	if (match(TokenType::ELSE)) {
		elseStatement = parseStatementOrBlockOfStatements();
	}

	return std::make_unique<ConditionalStatement>(std::move(conditional), std::move(ifStatement), std::move(elseStatement));
}

SPtr Parser::parseWhileStatement() {
	EPtr condition = parseExpression();

    expressionParsingErrorCheck(condition.get(), "Missing conditional expression");

	SPtr statement = parseStatementOrBlockOfStatements();
	return std::make_unique<WhileStatement>(std::move(condition), std::move(statement));
}

SPtr Parser::parseDoWhileStatement() {
	SPtr statement = parseStatementOrBlockOfStatements();
    consume(TokenType::WHILE);
	EPtr condition = parseExpression();

    expressionParsingErrorCheck(condition.get(), "Missing conditional expression");

    consume(TokenType::SEMICOLON);
	return std::make_unique<DoWhileStatement>(std::move(condition), std::move(statement));
}

SPtr Parser::parseForStatement() {
	if (match(TokenType::OPEN_BRACKET)) {
		SPtr initialization;

		if (match(TokenType::VAR)) {
			initialization = parseVariableDefinitionStatement();
		} else {
			initialization = parseAssignmentStatement();
		}

		match(TokenType::SEMICOLON);
		EPtr condition = parseExpression();

        expressionParsingErrorCheck(condition.get(), "Missing conditional expression");

		match(TokenType::SEMICOLON);
		SPtr increment = parseAssignmentStatement();

		if (!match(TokenType::CLOSE_BRACKET)) {
            throw LangException(ExceptionType::ParserError, "Missing expression or )", getPositionAfterToken(position - 1));
		}

		SPtr statement = parseStatementOrBlockOfStatements();
		return std::make_unique<ForStatement>(std::move(initialization), std::move(condition), std::move(increment), std::move(statement));
	} else {
		throw LangException(ExceptionType::ParserError, "Missing (", getPositionAfterToken(position - 1));
	}
}

SPtr Parser::parseContinueStatement() {
    SPtr statementTemp = std::make_unique<ContinueStatement>();
    consume(TokenType::SEMICOLON);
    return statementTemp;
}

SPtr Parser::parseBreakStatement() {
    SPtr statementTemp = std::make_unique<BreakStatement>();
    consume(TokenType::SEMICOLON);
    return statementTemp;
}

SPtr Parser::parseReturnStatement() {
    EPtr expr = parseExpression();
    SPtr statementTemp = std::make_unique<ReturnStatement>(std::move(expr));
    consume(TokenType::SEMICOLON);
    return statementTemp;
}

EPtr Parser::parseArrayExpression() {
	std::vector<EPtr> expressions;
    EPtr expr = nullptr;

    consume(TokenType::OPEN_SQUARE_BRACKET);

    if (!lookMatch(TokenType::CLOSE_SQUARE_BRACKET)) {
        do {
            expr = parseExpression();

            expressionParsingErrorCheck(expr.get(), "Missing expression or ]");

            expressions.emplace_back(std::move(expr));

        } while(match(TokenType::COMMA));
    }

    consume(TokenType::CLOSE_SQUARE_BRACKET);
	return std::make_unique<ArrayExpression>(std::move(expressions));
}

EPtr Parser::parseObjectExpression() {
    std::map<std::string, EPtr> dictionary;

    consume(TokenType::OPEN_BRACES);

    if (!lookMatch(TokenType::CLOSE_BRACES)) {
        do {
            std::string attribute = consume(TokenType::WORD).getValue();

            consume(TokenType::COLON);

            EPtr expr = parseExpression();

            expressionParsingErrorCheck(expr.get(), "Missing expression");

            dictionary.insert(std::pair<std::string, EPtr>(attribute, std::move(expr)));

        } while(match(TokenType::COMMA));
    }

    consume(TokenType::CLOSE_BRACES);
    return std::make_unique<ObjectExpression>(std::move(dictionary));
}

EPtr Parser::parseObjectLikeAccessExpression() {
    std::string variableName = consume(TokenType::WORD).getValue();
    EPtr variable = std::make_unique<VariableExpression>(variableName);

    do {
        consume(TokenType::DOT);

        std::string attribute = consume(TokenType::WORD).getValue();

        variable = std::make_unique<ArrayLikeAccessExpression>(std::move(variable), std::make_unique<ValueExpression>(attribute));

    } while(lookMatch(TokenType::DOT));

    return variable;
}

EPtr Parser::parseArrayLikeAccessExpression() {
	std::string variableName = consume(TokenType::WORD).getValue();
	EPtr variable = std::make_unique<VariableExpression>(variableName);

	do {
		consume(TokenType::OPEN_SQUARE_BRACKET);

		EPtr index = parseExpression();

        expressionParsingErrorCheck(index.get(), "Missing expression");

		consume(TokenType::CLOSE_SQUARE_BRACKET);

		variable = std::make_unique<ArrayLikeAccessExpression>(std::move(variable), std::move(index));
	} while(lookMatch(TokenType::OPEN_SQUARE_BRACKET));
	
	return variable;
}

EPtr Parser::parseFunctionExpression() {
	std::string functionName = consume(TokenType::WORD).getValue();
    std::vector<std::unique_ptr<IExpression>> args;
    EPtr expr = nullptr;

	consume(TokenType::OPEN_BRACKET);

    if (!lookMatch(TokenType::CLOSE_BRACKET)) {
        do {
            expr = parseExpression();

            expressionParsingErrorCheck(expr.get(), "Missing expression or )");

            args.emplace_back(std::move(expr));

        } while(match(TokenType::COMMA));
    }

	consume(TokenType::CLOSE_BRACKET);

    return std::make_unique<FunctionExpression>(functionName, std::move(args));
}

EPtr Parser::parseFunctionExpressionWithSemicolon() {
    EPtr function = parseFunctionExpression();
    consume(TokenType::SEMICOLON);
    return function;
}

EPtr Parser::parseExpression() {
	return parseLogicaOrExpression();
}

EPtr Parser::parseSubExpression() {
    EPtr result = parseExpression();

    expressionParsingErrorCheck(result.get(), "Missing expression");

    if (!match(TokenType::CLOSE_BRACKET)) {
        throw LangException(ExceptionType::ParserError, "Missing )", getPositionAfterToken(position - 1));
    }

    return result;
}

EPtr Parser::parseLogicaOrExpression() {
	EPtr result = parseLogicalAndExpression();

    while (match(TokenType::LOGICAL_OR)) {
        result = std::make_unique<BinaryExpression>(TokenType::LOGICAL_OR, std::move(result), parseLogicalAndExpression());
    }

	return result;
}

EPtr Parser::parseLogicalAndExpression() {
	EPtr result = parseEqualityExpression();

    while (match(TokenType::LOGICAL_AND)) {
        result = std::make_unique<BinaryExpression>(TokenType::LOGICAL_AND, std::move(result), parseEqualityExpression());
    }

	return result;
}

EPtr Parser::parseEqualityExpression() {
	EPtr result = parseComparisonExpression();

	while (true) {
		if (match(TokenType::EQUALS)) {
			result = std::make_unique<BinaryExpression>(TokenType::EQUALS, std::move(result), parseComparisonExpression());
			continue;
		}

		if (match(TokenType::NOT_EQUALS)) {
			result = std::make_unique<BinaryExpression>(TokenType::NOT_EQUALS, std::move(result), parseComparisonExpression());
			continue;
		}

		break;
	}

	return result;
}

EPtr Parser::parseComparisonExpression() {
	EPtr result = parseAdditiveExpression();

	while (true) {
		if (match(TokenType::GREATER_THAN)) {
			result = std::make_unique<BinaryExpression>(TokenType::GREATER_THAN, std::move(result), parseAdditiveExpression());
			continue;
		}

		if (match(TokenType::GREATER_OR_EQUALS)) {
			result = std::make_unique<BinaryExpression>(TokenType::GREATER_OR_EQUALS, std::move(result), parseAdditiveExpression());
			continue;
		}

		if (match(TokenType::LESS_THAN)) {
			result = std::make_unique<BinaryExpression>(TokenType::LESS_THAN, std::move(result), parseAdditiveExpression());
			continue;
		}

		if (match(TokenType::LESS_OR_EQUALS)) {
			result = std::make_unique<BinaryExpression>(TokenType::LESS_OR_EQUALS, std::move(result), parseAdditiveExpression());
			continue;
		}

		break;
	}

	return result;
}

EPtr Parser::parseAdditiveExpression() {
	EPtr result = parseMultiplicativeExpression();

	while (true) {
		if (match(TokenType::PLUS)) {
			result = std::make_unique<BinaryExpression>(TokenType::PLUS, std::move(result), parseMultiplicativeExpression());
			continue;
		}

		if (match(TokenType::MINUS)) {
			result = std::make_unique<BinaryExpression>(TokenType::MINUS, std::move(result), parseMultiplicativeExpression());
			continue;
		}

		break;
	}

	return result;
}

EPtr Parser::parseMultiplicativeExpression() {
	EPtr result = parseUnaryExpression();

	while (true) {
		if (match(TokenType::MULTIPLY)) {
			result = std::make_unique<BinaryExpression>(TokenType::MULTIPLY, std::move(result), parseUnaryExpression());
			continue;
		}

		if (match(TokenType::DIVISION)) {
			result = std::make_unique<BinaryExpression>(TokenType::DIVISION, std::move(result), parseUnaryExpression());
			continue;
		}

		if (match(TokenType::MOD)) {
			result = std::make_unique<BinaryExpression>(TokenType::MOD, std::move(result), parseUnaryExpression());
			continue;
		}

		if (match(TokenType::DIV)) {
			result = std::make_unique<BinaryExpression>(TokenType::DIV, std::move(result), parseUnaryExpression());
			continue;
		}

		break;
	}

	return result;
}

EPtr Parser::parseUnaryExpression() {
	if (match(TokenType::MINUS)) {
		return std::make_unique<UnaryExpression>(TokenType::MINUS, parsePrimaryExpression());
	}

	if (match(TokenType::PLUS)) {
		return std::make_unique<UnaryExpression>(TokenType::PLUS, parsePrimaryExpression());
	}

	if (match(TokenType::LOGICAL_NOT)) {
		return std::make_unique<UnaryExpression>(TokenType::LOGICAL_NOT, parsePrimaryExpression());
	}

	return parsePrimaryExpression();
}

EPtr Parser::parsePrimaryExpression() {
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
		return parseFunctionExpression();
	}

	if (lookMatch(TokenType::WORD) && lookMatch(TokenType::OPEN_SQUARE_BRACKET, 1)) {
		return parseArrayLikeAccessExpression();
	}

    if (lookMatch(TokenType::WORD) && lookMatch(TokenType::DOT, 1)) {
        return parseObjectLikeAccessExpression();
    }

	if (match(TokenType::WORD)) {
		return std::make_unique<VariableExpression>(token.getValue());
	}

	if (lookMatch(TokenType::OPEN_SQUARE_BRACKET)) {
		return parseArrayExpression();
	}

    if (lookMatch(TokenType::OPEN_BRACES)) {
        return parseObjectExpression();
    }

	if (match(TokenType::OPEN_BRACKET)) {
		return parseSubExpression();
	}

    return nullptr;
}

const Token& Parser::getToken(const size_t relativePos) const {
	size_t pos = position + relativePos;

	if (pos >= size) {
		return eof;
	}

	return tokens[pos];
}

const Token& Parser::consume(const TokenType type) {
	if (type == getToken().getType()) {
		return tokens[position++];
	}

    throw LangException(ExceptionType::ParserError, "Missing " + Token::toString(type), getPositionAfterToken(position - 1));
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