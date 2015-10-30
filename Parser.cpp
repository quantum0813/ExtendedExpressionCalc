#include "Parser.hpp"
#include "Lexer.hpp"
#include "AST.hpp"

#include <string>
#include <assert.h>

Expression * Parser::Parse() {
    if (mTokenList.size() == 0)
        throw ParserException("Token list can't be null or empty!");

    next();
    return expression();
}

void Parser::next() {
    do {
        if (mCurrentIndex < mTokenList.size()) {
            mLookAhead = mTokenList[mCurrentIndex];
            mCurrentIndex++;
        }
    } while (mLookAhead.getType() == TokenType::WHITESPACE);
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
                e = new SubtractionExpression(e, e2);
                break;
        }
    }
    return e;
}

Expression * Parser::multiplicativeExpr() {
    Expression * e = primaryExpr();
    while (mLookAhead.getType() == TokenType::MULTIPLY || mLookAhead.getType() == TokenType::DIVIDE || mLookAhead.getType() == TokenType::MOD) {
        Expression * e2 = nullptr;
        switch (mLookAhead.getType()) {
            case TokenType::MULTIPLY:
                next();
                e2 = primaryExpr();
                e = new MultiplicationExpression(e, e2);
                break;
            case TokenType::DIVIDE:
                next();
                e2 = primaryExpr();
                e = new DivisionExpression(e, e2);
                break;
            case TokenType::MOD:
                next();
                e2 = primaryExpr();
                e = new ModExpression(e, e2);
                break;
        }
    }
    return e;
}

Expression * Parser::primaryExpr() {
    if (mLookAhead.getType() == TokenType::TRUE || mLookAhead.getType() == TokenType::FALSE || mLookAhead.getType() == TokenType::NUMBER || mLookAhead.getType() == TokenType::PLUS || mLookAhead.getType() == TokenType::MINUS || mLookAhead.getType() == TokenType::NOT) {
        switch (mLookAhead.getType()) {
            case TokenType::TRUE:
                next();
                return new Value(true);
            case TokenType::FALSE:
                next();
                return new Value(false);
            case TokenType::NUMBER: {
                int val = atoi(mLookAhead.getText()->c_str());
                next();
                return new Value(val);
            }
            case TokenType::PLUS: {
                next();
                int val2 = atoi(mLookAhead.getText()->c_str());
                next();
                return new PositiveExpression(new Value(val2));
            }
            case TokenType::MINUS: {
                next();
                int val3 = atoi(mLookAhead.getText()->c_str());
                next();
                return new NegationExpression(new Value(val3));
            }
            case TokenType::NOT: {
                next();
                bool val4 = mLookAhead.getType() == TokenType::TRUE;
                next();
                return new NotExpression(new Value(val4));
            }
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
    } else {
        // Unexpected token
        // Throw exception
    }
}