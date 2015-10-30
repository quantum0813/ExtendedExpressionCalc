#ifndef EXTENDEDCALC_PARSER_HPP
#define EXTENDEDCALC_PARSER_HPP

#include <vector>
#include "AST.hpp"
#include "Lexer.hpp"

class Parser {
    public:
        Parser(std::vector<Token> tokens) : mTokenList(tokens), mCurrentIndex(0) {}
        Expression * Parse();
    private:
        std::vector<Token> mTokenList;
        Token mLookAhead;
        int mCurrentIndex;

        void next();
        Expression * expression();
        Expression * logicalOrExpr();
        Expression * logicalAndExpr();
        Expression * equalityExpr();
        Expression * orderingExpr();
        Expression * additiveExpr();
        Expression * multiplicativeExpr();
        Expression * unaryExpr();
        Expression * primaryExpr();
};

class ParserException {
public:
    ParserException(std::string msg) : mWhat(msg) {}
    ParserException(std::string msg, int loc) : mWhat(msg), mLocation(loc) {}

    std::string & what() {
        return mWhat;
    }

    int location() {
        return mLocation;
    }
private:
    std::string mWhat;
    int mLocation;
};

#endif //EXTENDEDCALC_PARSER_HPP