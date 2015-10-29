#include <iostream>
#include <sstream>
#include <vector>
#include "Type.hpp"
#include "AST.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"

using namespace std;

int main() {
    std::cout << getIntType() << std::endl;
    std::cout << getBoolType() << std::endl;

    //AddExpr * e = new AddExpr(new Number(3), new Number(4));
    //e->setType(getIntType());

    /*IntValue * val = new IntValue(4);
    BoolValue * val2 = new BoolValue(true);
    Expression * e = new AdditionExpression(new AdditionExpression(new IntValue(2), new IntValue(2)), new IntValue(4));
    Expression * e2 = new LogicalOrExpression(new LogicalAndExpression(new BoolValue(true), new BoolValue(false)), new BoolValue(false));*/
    //Expression * e3 = new EqualExpression(new IntValue(3), new IntValue(3));
    //Expression * e = new NegationExpression(new NegationExpression(new NegationExpression(new IntValue(5))));
    //Expression * e2 = new PositiveExpression(e);
    Expression * e = new AdditionExpression(new NegationExpression(new Value(3)), new NegationExpression(new Value(4)));
    Expression * e2 = new NotExpression(new EqualExpression(new Value(5), new Value(5)));
    EvaluateVisitor * visitor = new EvaluateVisitor();
    /*val->accept(visitor);
    val2->accept(visitor);
    e->accept(visitor);
    e2->accept(visitor);*/
    //e3->accept(visitor);
    e->accept(visitor);
    e2->accept(visitor);

    stringstream ss("200+100");
    Lexer l = Lexer(ss);
    vector<Token> tokens;
    try {
        tokens = l.Lex();
    } catch (LexerException & ex) {
        std::cout << ex.what() << std::endl;
    }

    Parser p = Parser(tokens);
    Expression * expr = p.Parse();

    expr->accept(visitor);

    cout << endl << endl;
    cout << "Type\t\t\tValue" << endl;
    cout << "====\t\t\t=====" << endl << endl;
    for (int i = 0; i < tokens.size(); i++) {
        cout << TOKEN_TYPE_VALUES[tokens[i].getType()] << "\t\t\t\t" << *tokens[i].getText() << endl;
    }

    /*delete val;
    delete val2;
    delete e;
    delete e2;*/
    //delete e3;
    delete visitor;
}