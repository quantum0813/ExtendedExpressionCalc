#include "Parser.hpp"
#include "Lexer.hpp"
#include "AST.hpp"

#include <string>

Expression * Parser::Parse() {
    if (mTokenList.size() == 0)
        throw ParserException("Token list can't be null or empty!");

    next();
    return expression();
}

void Parser::next() {
    mLookAhead = mTokenList[mCurrentIndex];
    mCurrentIndex++;
}

Expression * Parser::expression() {
    return logicalOrExpr();
}

Expression * Parser::logicalOrExpr() {
    Expression * e = logicalAndExpr();
    while (mLookAhead.getType() == TokenType::OR) {
        Expression * e2 = nullptr;
        switch (mLookAhead.getType()) {
            case TokenType::OR:
                next();
                e2 = logicalAndExpr();
                e = new LogicalOrExpression(e, e2);
                break;
        }
    }
    return e;
}

Expression * Parser::logicalAndExpr() {
    Expression * e = equalityExpr();
    while (mLookAhead.getType() == TokenType::AND) {
        Expression * e2 = nullptr;
        switch (mLookAhead.getType()) {
            case TokenType::AND:
                next();
                e2 = equalityExpr();
                e = new LogicalAndExpression(e, e2);
                break;
        }
    }
    return e;
}

Expression * Parser::equalityExpr() {
    Expression * e = orderingExpr();
    while (mLookAhead.getType() == TokenType::EQUAL || mLookAhead.getType() == TokenType::NEQ) {
        Expression * e2 = nullptr;
        switch (mLookAhead.getType()) {
            case TokenType::EQUAL:
                next();
                e2 = orderingExpr();
                e = new EqualExpression(e, e2);
                break;
            case TokenType::NEQ:
                next();
                e2 = orderingExpr();
                e = new NotEqualExpression(e, e2);
                break;
        }
    }
    return e;
}

Expression * Parser::orderingExpr() {
    Expression * e = additiveExpr();
    while (mLookAhead.getType() == TokenType::LT || mLookAhead.getType() == TokenType::GT || mLookAhead.getType() == TokenType::LTE || mLookAhead.getType() == TokenType::GTE) {
        Expression * e2 = nullptr;
        switch (mLookAhead.getType()) {
            case TokenType::LT:
                next();
                e2 = additiveExpr();
                e = new LessThanExpression(e, e2);
                break;
            case TokenType::GT:
                next();
                e2 = additiveExpr();
                e = new GreaterThanExpression(e, e2);
                break;
            case TokenType::LTE:
                next();
                e2 = additiveExpr();
                e = new LessThanEqualExpression(e, e2);
                break;
            case TokenType::GTE:
                next();
                e2 = additiveExpr();
                e = new GreaterThanEqualExpression(e, e2);
                break;
        }
    }
    return e;
}

Expression * Parser::additiveExpr() {
    Expression * e = multiplicativeExpr();
    while (mLookAhead.getType() == TokenType::PLUS || mLookAhead.getType() == TokenType::MINUS) {
        Expression * e2 = nullptr;
        switch (mLookAhead.getType()) {
            case TokenType::PLUS:
                next();
                e2 = multiplicativeExpr();
                e = new AdditionExpression(e, e2);
                break;
            case TokenType::MINUS:
                next();
                e2 = multiplicativeExpr();
                e = new AdditionExpression(e, e2);
                break;
        }
    }
    return e;
}

Expression * Parser::multiplicativeExpr() {
    Expression * e = unaryExpr();
    while (mLookAhead.getType() == TokenType::MULTIPLY || mLookAhead.getType() == TokenType::DIVIDE || mLookAhead.getType() == TokenType::MOD) {
        Expression * e2 = nullptr;
        switch (mLookAhead.getType()) {
            case TokenType::MULTIPLY:
                next();
                e2 = unaryExpr();
                e = new MultiplicationExpression(e, e2);
                break;
            case TokenType::DIVIDE:
                next();
                e2 = unaryExpr();
                e = new DivisionExpression(e, e2);
                break;
            case TokenType::MOD:
                next();
                e2 = unaryExpr();
                e = new ModExpression(e, e2);
                break;
        }
    }
    return e;
}

Expression * Parser::unaryExpr() {
    Expression * e = primaryExpr();
    while (mLookAhead.getType() == TokenType::MINUS || mLookAhead.getType() == TokenType::PLUS || mLookAhead.getType() == TokenType::NOT) {
        switch (mLookAhead.getType()) {
            case TokenType::MINUS:
                next();
                e = new NegationExpression(e);
                break;
            case TokenType::PLUS:
                next();
                e = new PositiveExpression(e);
                break;
            case TokenType::NOT:
                next();
                e = new NotExpression(e);
                break;
        }
    }
    return e;
}

Expression * Parser::primaryExpr() {
    if (mLookAhead.getType() == TokenType::TRUE || mLookAhead.getType() == TokenType::FALSE ||
                                                   mLookAhead.getType() == TokenType::NUMBER) {
        switch (mLookAhead.getType()) {
            case TokenType::TRUE:
                next();
                return new Value(true);
            case TokenType::FALSE:
                next();
                return new Value(false);
            case TokenType::NUMBER:
                int val = atoi(mLookAhead.getText()->c_str());
                next();
                return new Value(val);
        }
    } else if (mLookAhead.getType() == TokenType::LPAREN) {
        next();
        Expression * e = expression();
        if (mLookAhead.getType() != TokenType::RPAREN) {
            // Syntax error!
            // Throw exception
        }
        next();
        return e;
    } else if (mLookAhead.getType() == TokenType::WHITESPACE) {
        // Skip the whitespace token
        next();
    } else {
        // Unexpected token
        // Throw exception
    }
}